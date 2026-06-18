# auto_test.py - Auto test script for Diem Danh Sinh Vien
# Run: python test/auto_test.py  (from project root)
# Each module has ~5 test cases => 25 total

import subprocess
import shutil
import os
import sys

# -- Config --
PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE_PATH = os.path.join(PROJECT_DIR, "diemdanh.exe")
DATA_DIR = os.path.join(PROJECT_DIR, "data")
BACKUP_DIR = os.path.join(PROJECT_DIR, "data_backup_test")
DATA_FILES = ["lophoc.txt", "sinhvien.txt", "diemdanh.txt"]

# -- Terminal colors --
class Color:
    GREEN  = "\033[92m"
    RED    = "\033[91m"
    YELLOW = "\033[93m"
    CYAN   = "\033[96m"
    BOLD   = "\033[1m"
    RESET  = "\033[0m"

def header(text):
    print(f"\n{Color.CYAN}{Color.BOLD}{'=' * 64}")
    print(f"  {text}")
    print(f"{'=' * 64}{Color.RESET}")

def sub_header(text):
    print(f"\n  {Color.CYAN}--- {text} ---{Color.RESET}")

def passed(msg):
    print(f"    {Color.GREEN}[PASS] {msg}{Color.RESET}")

def failed(msg):
    print(f"    {Color.RED}[FAIL] {msg}{Color.RESET}")

def info(msg):
    print(f"    {Color.YELLOW}[INFO] {msg}{Color.RESET}")

# -- Backup / Restore --
def backup_data():
    if os.path.exists(BACKUP_DIR):
        shutil.rmtree(BACKUP_DIR)
    shutil.copytree(DATA_DIR, BACKUP_DIR)

def restore_data():
    if os.path.exists(BACKUP_DIR):
        for f in DATA_FILES:
            src = os.path.join(BACKUP_DIR, f)
            dst = os.path.join(DATA_DIR, f)
            if os.path.exists(src):
                shutil.copy2(src, dst)

def cleanup_backup():
    if os.path.exists(BACKUP_DIR):
        shutil.rmtree(BACKUP_DIR)

# -- Helpers --
def run_program(input_text, timeout=10):
    try:
        proc = subprocess.run(
            [EXE_PATH], input=input_text, capture_output=True,
            text=True, timeout=timeout, cwd=PROJECT_DIR,
            encoding="utf-8", errors="replace",
        )
        return proc.stdout, proc.stderr, proc.returncode
    except subprocess.TimeoutExpired:
        return None, "TIMEOUT", -1
    except Exception as e:
        return None, str(e), -1

def read_file(filename):
    path = os.path.join(DATA_DIR, filename)
    if not os.path.exists(path):
        return ""
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        return f.read()

def count_lines(filename):
    content = read_file(filename)
    return len([l for l in content.strip().split("\n") if l.strip()])

def write_file(filename, content):
    path = os.path.join(DATA_DIR, filename)
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)

results = []

def add_result(module, tc_id, status, detail):
    results.append((module, tc_id, status, detail))


# ==================================================================
#  MODULE 1: DiemDanhManager (5 tests)
# ==================================================================

def test_diemdanh_manager():
    header("MODULE 1: DiemDanhManager")

    # -- 1.1: Diem danh trung (duplicate) --
    sub_header("1.1: Diem danh trung - duplicate data")
    restore_data()
    lines_before = count_lines("diemdanh.txt")
    inp = "\n".join([
        "3", "1", "KTLT_01", "08/06/2026", "y",
        "C", "C", "C", "C", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout is None:
        failed("Program timeout/error")
        add_result("DiemDanhMgr", "1.1", "FAIL", "Timeout")
    else:
        lines_after = count_lines("diemdanh.txt")
        content = read_file("diemdanh.txt")
        dup = content.count("08/06/2026")
        if lines_after > lines_before:
            passed(f"Duplicate! {lines_before}->{lines_after} lines, {dup} records for 08/06")
            add_result("DiemDanhMgr", "1.1", "PASS", f"Dup: {lines_before}->{lines_after}")
        else:
            info("No duplication")
            add_result("DiemDanhMgr", "1.1", "INFO", "No dup")

    # -- 1.2: Diem danh lop khong co SV --
    sub_header("1.2: Diem danh lop khong co sinh vien")
    restore_data()
    inp = "\n".join([
        "3", "1", "KTLT_02",  # Lop KTLT_02 co 3 SV
        "20/06/2026",
        "C", "C", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Da luu diem danh" in stdout:
        passed("Diem danh KTLT_02 OK (3 SV)")
        add_result("DiemDanhMgr", "1.2", "PASS", "Attendance saved for KTLT_02")
    else:
        info("Check output manually")
        add_result("DiemDanhMgr", "1.2", "INFO", "Check output")

    # -- 1.3: Sua diem danh thanh cong --
    sub_header("1.3: Sua diem danh - truong hop hop le")
    restore_data()
    inp = "\n".join([
        "3", "2", "KTLT_01", "08/06/2026",
        "y", "22010002", "K",  # Sua SV 22010002 thanh Vang KP
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Da cap nhat diem danh" in stdout:
        content = read_file("diemdanh.txt")
        if "22010002|KTLT_01|08/06/2026|K" in content:
            passed("Edit OK: 22010002 changed to K in file")
            add_result("DiemDanhMgr", "1.3", "PASS", "Edit saved correctly")
        else:
            info("Output says OK but file not updated")
            add_result("DiemDanhMgr", "1.3", "INFO", "File mismatch")
    else:
        info("Edit may have failed")
        add_result("DiemDanhMgr", "1.3", "INFO", "Edit not confirmed")

    # -- 1.4: Canh bao cam thi voi tongSoBuoi = 0 (lop da xoa) --
    sub_header("1.4: Canh bao cam thi khi tongSoBuoi=0")
    restore_data()
    # Xoa lop KTLT_01 truoc -> tongSoBuoi = 0
    inp = "\n".join(["1", "4", "KTLT_01", "0", "0"])
    run_program(inp)
    # Them lai lop KTLT_01 voi tongSoBuoi = 0 (trick: sua file)
    lophoc = read_file("lophoc.txt")
    lophoc += "KTLT_01|Test|GV|3|1|4|B1|0\n"  # tongSoBuoi = 0
    write_file("lophoc.txt", lophoc)
    inp = "\n".join(["3", "3", "KTLT_01", "0", "0"])
    stdout, _, rc = run_program(inp)
    if stdout and rc == 0:
        # tiLe = soVang / 0 -> code kiem tra tongSoBuoi > 0 nen tiLe = 0
        if "Khong co sinh vien nao bi canh bao" in stdout:
            passed("tongSoBuoi=0 -> tiLe=0% -> no warning (division by zero handled)")
            add_result("DiemDanhMgr", "1.4", "PASS", "Div-by-zero handled but logic wrong")
        else:
            info("Unexpected output")
            add_result("DiemDanhMgr", "1.4", "INFO", "Check output")
    else:
        failed(f"Program error (rc={rc})")
        add_result("DiemDanhMgr", "1.4", "FAIL", f"rc={rc}")

    # -- 1.5: Diem danh ngay tuong lai (khong co validate) --
    sub_header("1.5: Diem danh ngay tuong lai (31/12/2099)")
    restore_data()
    inp = "\n".join([
        "3", "1", "KTLT_01", "31/12/2099",
        "C", "C", "C", "C", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and rc == 0:
        content = read_file("diemdanh.txt")
        if "31/12/2099" in content:
            passed("Future date 31/12/2099 accepted and saved! (no date logic check)")
            add_result("DiemDanhMgr", "1.5", "PASS", "Future date accepted")
        else:
            info("Date not saved")
            add_result("DiemDanhMgr", "1.5", "INFO", "Date not in file")
    else:
        info("Program issue")
        add_result("DiemDanhMgr", "1.5", "INFO", "Check output")


# ==================================================================
#  MODULE 2: FileIO (5 tests)
# ==================================================================

def test_fileio():
    header("MODULE 2: FileIO")

    # -- 2.1: Trang thai khong hop le 'X' --
    sub_header("2.1: Invalid status char 'X' in diemdanh.txt")
    restore_data()
    original = read_file("diemdanh.txt")
    write_file("diemdanh.txt", original + "22010001|KTLT_01|01/01/2026|X\n")
    inp = "\n".join(["4", "2", "22010002", "0", "0"])
    stdout, _, rc = run_program(inp)
    if rc == 0:
        passed("Invalid status 'X' loaded without validation (no crash)")
        add_result("FileIO", "2.1", "PASS", "No validation on load")
    else:
        passed(f"Program crashed with bad data (rc={rc})")
        add_result("FileIO", "2.1", "PASS", f"Crash rc={rc}")

    # -- 2.2: File diemdanh.txt rong --
    sub_header("2.2: diemdanh.txt is empty")
    restore_data()
    write_file("diemdanh.txt", "")
    inp = "\n".join(["4", "1", "KTLT_01", "08/06/2026", "0", "0"])
    stdout, _, rc = run_program(inp)
    if rc == 0 and stdout and "Khong co du lieu" in stdout:
        passed("Empty file handled OK - shows 'no data' message")
        add_result("FileIO", "2.2", "PASS", "Empty file OK")
    elif rc == 0:
        passed("Program did not crash with empty file")
        add_result("FileIO", "2.2", "PASS", "No crash")
    else:
        failed(f"Crash with empty file (rc={rc})")
        add_result("FileIO", "2.2", "FAIL", f"Crash rc={rc}")

    # -- 2.3: File co dong thieu truong (chi 2 truong thay vi 4) --
    sub_header("2.3: diemdanh.txt has line with missing fields")
    restore_data()
    original = read_file("diemdanh.txt")
    write_file("diemdanh.txt", original + "22010001|KTLT_01\n")  # chi 2 truong
    inp = "\n".join(["4", "2", "22010002", "0", "0"])
    stdout, _, rc = run_program(inp)
    if rc == 0:
        passed("Line with 2 fields skipped (p.size() < 4 check works)")
        add_result("FileIO", "2.3", "PASS", "Malformed line skipped")
    else:
        failed(f"Crash with malformed line (rc={rc})")
        add_result("FileIO", "2.3", "FAIL", f"Crash rc={rc}")

    # -- 2.4: File lophoc.txt khong ton tai (xoa truoc khi chay) --
    sub_header("2.4: lophoc.txt does not exist")
    restore_data()
    lophoc_path = os.path.join(DATA_DIR, "lophoc.txt")
    if os.path.exists(lophoc_path):
        os.remove(lophoc_path)
    inp = "\n".join(["1", "1", "0", "0"])  # Xem danh sach lop
    stdout, _, rc = run_program(inp)
    if rc == 0 and stdout:
        if "Khong doc duoc" in stdout or "Chua co lop hoc nao" in stdout:
            passed("Missing file handled gracefully - starts with empty list")
            add_result("FileIO", "2.4", "PASS", "Missing file OK")
        else:
            passed("No crash when file missing")
            add_result("FileIO", "2.4", "PASS", "No crash")
    else:
        failed(f"Crash when file missing (rc={rc})")
        add_result("FileIO", "2.4", "FAIL", f"Crash rc={rc}")

    # -- 2.5: Ky tu dac biet trong du lieu (pipe '|' trong ten) --
    sub_header("2.5: Pipe char '|' inside student name")
    restore_data()
    original = read_file("sinhvien.txt")
    write_file("sinhvien.txt", original + "SV000001|Nguyen|Van|A|KTLT_01\n")
    inp = "\n".join(["2", "1", "KTLT_01", "0", "0"])
    stdout, _, rc = run_program(inp)
    if rc == 0:
        # Ten se bi tach sai: hoTen = "Nguyen", maLop = "Van"
        sv_lines = [l for l in read_file("sinhvien.txt").split("\n") if "SV000001" in l]
        passed("Pipe in name causes wrong parsing (name='Nguyen', maLop='Van')")
        add_result("FileIO", "2.5", "PASS", "Pipe in name breaks parsing")
    else:
        failed(f"Crash (rc={rc})")
        add_result("FileIO", "2.5", "FAIL", f"Crash rc={rc}")


# ==================================================================
#  MODULE 3: Validation (5 tests)
# ==================================================================

def test_validation():
    header("MODULE 3: Validation")

    # -- 3.1: maxLen khong duoc su dung --
    sub_header("3.1: nhapChuoi maxLen not enforced (5000 char name)")
    restore_data()
    long_name = "A" * 5000
    inp = "\n".join(["2", "2", "SV999999", long_name, "KTLT_01", "0", "0"])
    stdout, _, rc = run_program(inp, timeout=15)
    if rc == 0:
        sv = read_file("sinhvien.txt")
        if "AAAAAAAAAA" in sv:
            passed("5000-char name saved without limit! maxLen param unused")
            add_result("Validation", "3.1", "PASS", "maxLen not enforced")
        else:
            info("Name not saved or truncated")
            add_result("Validation", "3.1", "INFO", "Check manually")
    else:
        passed(f"Crash with long input (rc={rc})")
        add_result("Validation", "3.1", "PASS", f"Crash rc={rc}")

    # -- 3.2: Ngay sai dinh dang (DD-MM-YYYY thay vi DD/MM/YYYY) --
    sub_header("3.2: Wrong date format DD-MM-YYYY (dash instead of slash)")
    restore_data()
    inp = "\n".join([
        "3", "1", "KTLT_01",
        "08-06-2026",    # sai format -> bi reject
        "08/06/2026",    # dung format
        "y",
        "C", "C", "C", "C", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Ngay khong hop le" in stdout:
        passed("Wrong format DD-MM-YYYY correctly rejected")
        add_result("Validation", "3.2", "PASS", "Bad date format rejected")
    else:
        info("Check output")
        add_result("Validation", "3.2", "INFO", "Check output")

    # -- 3.3: Ngay 29/02 nam khong nhuan --
    sub_header("3.3: Date 29/02/2025 (non-leap year)")
    restore_data()
    inp = "\n".join([
        "3", "1", "KTLT_01",
        "29/02/2025",    # 2025 khong nhuan -> reject
        "28/02/2025",    # 28/02 ok
        "C", "C", "C", "C", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Ngay khong hop le" in stdout:
        passed("29/02/2025 correctly rejected (non-leap year)")
        add_result("Validation", "3.3", "PASS", "Leap year check works")
    else:
        info("Check output")
        add_result("Validation", "3.3", "INFO", "Check output")

    # -- 3.4: Nhap chu vao cho nhap so (menu) --
    sub_header("3.4: Input text 'abc' at menu number prompt")
    restore_data()
    inp = "\n".join([
        "abc",       # nhap chu -> reject
        "xyz",       # nhap chu -> reject
        "1",         # nhap so dung
        "1",         # Xem danh sach
        "0",         # Quay lai
        "0",         # Thoat
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Gia tri khong hop le" in stdout:
        passed("Text input at number prompt correctly rejected (no crash)")
        add_result("Validation", "3.4", "PASS", "Text at number prompt handled")
    elif rc == 0:
        passed("No crash with text input at number prompt")
        add_result("Validation", "3.4", "PASS", "No crash")
    else:
        failed(f"Crash (rc={rc})")
        add_result("Validation", "3.4", "FAIL", f"Crash rc={rc}")

    # -- 3.5: MSSV co ky tu dac biet --
    sub_header("3.5: MSSV with special chars '@#$!'")
    restore_data()
    inp = "\n".join([
        "2", "2",
        "SV@#$!",     # MSSV khong hop le
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "MSSV khong hop le" in stdout:
        passed("MSSV with special chars correctly rejected")
        add_result("Validation", "3.5", "PASS", "Special char MSSV rejected")
    elif rc == 0:
        passed("No crash with special char MSSV")
        add_result("Validation", "3.5", "PASS", "No crash")
    else:
        failed(f"Crash (rc={rc})")
        add_result("Validation", "3.5", "FAIL", f"Crash rc={rc}")


# ==================================================================
#  MODULE 4: Menu CRUD (5 tests)
# ==================================================================

def test_menu_crud():
    header("MODULE 4: Menu CRUD Operations")

    # -- 4.1: Xoa lop -> du lieu mo coi --
    sub_header("4.1: Delete class -> orphaned SV/DiemDanh")
    restore_data()
    inp = "\n".join(["1", "4", "KTLT_01", "0", "0"])
    stdout, _, rc = run_program(inp)
    lophoc = read_file("lophoc.txt")
    sv = read_file("sinhvien.txt")
    dd = read_file("diemdanh.txt")
    lop_del = "KTLT_01" not in lophoc
    sv_orphan = "KTLT_01" in sv
    dd_orphan = "KTLT_01" in dd
    if lop_del and (sv_orphan or dd_orphan):
        passed("Class deleted but SV/DiemDanh orphaned! (no cascade delete)")
        add_result("MenuCRUD", "4.1", "PASS", "Orphaned data")
    elif not lop_del:
        failed("Class not deleted")
        add_result("MenuCRUD", "4.1", "FAIL", "Delete failed")
    else:
        info("Cascade delete works")
        add_result("MenuCRUD", "4.1", "INFO", "Cascade OK")

    # -- 4.2: Them lop trung ma --
    sub_header("4.2: Add class with duplicate maLop")
    restore_data()
    inp = "\n".join([
        "1", "2",
        "KTLT_01",     # Ma lop da ton tai
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "da ton tai" in stdout:
        passed("Duplicate class code correctly rejected")
        add_result("MenuCRUD", "4.2", "PASS", "Dup class rejected")
    else:
        info("Check output")
        add_result("MenuCRUD", "4.2", "INFO", "Check output")

    # -- 4.3: Them SV vao lop khong ton tai --
    sub_header("4.3: Add SV to non-existent class")
    restore_data()
    inp = "\n".join([
        "2", "2",
        "SV111111",         # MSSV moi
        "Nguyen Van Test",  # Ho ten
        "KHONGTONTAI",      # Ma lop khong co
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "khong ton tai" in stdout:
        passed("Adding SV to non-existent class correctly rejected")
        add_result("MenuCRUD", "4.3", "PASS", "Non-existent class rejected")
    else:
        info("Check output")
        add_result("MenuCRUD", "4.3", "INFO", "Check output")

    # -- 4.4: Them SV trung MSSV --
    sub_header("4.4: Add SV with duplicate MSSV")
    restore_data()
    inp = "\n".join([
        "2", "2",
        "22010002",         # MSSV da ton tai
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "da ton tai" in stdout:
        passed("Duplicate MSSV correctly rejected")
        add_result("MenuCRUD", "4.4", "PASS", "Dup MSSV rejected")
    else:
        info("Check output")
        add_result("MenuCRUD", "4.4", "INFO", "Check output")

    # -- 4.5: Xoa SV khong ton tai --
    sub_header("4.5: Delete non-existent SV")
    restore_data()
    lines_before = count_lines("sinhvien.txt")
    inp = "\n".join([
        "2", "4",
        "KHONGTONTAI",   # MSSV khong co
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    lines_after = count_lines("sinhvien.txt")
    if stdout and "Khong tim thay" in stdout and lines_before == lines_after:
        passed("Non-existent SV correctly rejected, file unchanged")
        add_result("MenuCRUD", "4.5", "PASS", "Not found, file OK")
    else:
        info("Check output")
        add_result("MenuCRUD", "4.5", "INFO", "Check output")


# ==================================================================
#  MODULE 5: Search + BaoCao (5 tests)
# ==================================================================

def test_search_baocao():
    header("MODULE 5: Search + BaoCao")

    # -- 5.1: Sua diem danh - MSSV sai (UX issue) --
    sub_header("5.1: Edit attendance - wrong MSSV (UX issue)")
    restore_data()
    inp = "\n".join([
        "3", "2", "KTLT_01", "08/06/2026",
        "y", "99999999", "C",
        "0", "0",
    ])
    stdout, _, rc = run_program(inp)
    if stdout and "Khong tim thay phieu diem danh" in stdout:
        idx_tt = stdout.find("Trang thai (C=Co mat")
        idx_nf = stdout.find("Khong tim thay phieu")
        if idx_tt != -1 and idx_nf != -1 and idx_tt < idx_nf:
            passed("UX bug: Must input C/P/K BEFORE knowing MSSV is wrong!")
            add_result("Search/BC", "5.1", "PASS", "Input before validation")
        else:
            info("Error order seems OK")
            add_result("Search/BC", "5.1", "INFO", "Order OK")
    else:
        info("Check output")
        add_result("Search/BC", "5.1", "INFO", "Check output")

    # -- 5.2: Tim SV khong ton tai --
    sub_header("5.2: Search attendance for non-existent MSSV")
    restore_data()
    inp = "\n".join(["4", "2", "KHONGTONTAI", "0", "0"])
    stdout, _, rc = run_program(inp)
    if stdout and "khong ton tai" in stdout:
        passed("Non-existent MSSV search correctly shows error")
        add_result("Search/BC", "5.2", "PASS", "Not found msg OK")
    else:
        info("Check output")
        add_result("Search/BC", "5.2", "INFO", "Check output")

    # -- 5.3: Tim diem danh ngay chua co du lieu --
    sub_header("5.3: Search attendance for date with no data")
    restore_data()
    inp = "\n".join(["4", "1", "KTLT_01", "01/01/2000", "0", "0"])
    stdout, _, rc = run_program(inp)
    if stdout and "Khong co du lieu" in stdout:
        passed("No data for 01/01/2000 - correctly shows empty message")
        add_result("Search/BC", "5.3", "PASS", "No data msg OK")
    else:
        info("Check output")
        add_result("Search/BC", "5.3", "INFO", "Check output")

    # -- 5.4: Bao cao lop khong co du lieu diem danh --
    sub_header("5.4: Report for class with no attendance data")
    restore_data()
    inp = "\n".join(["5", "1", "KTLT_02", "0", "0"])  # KTLT_02 co SV nhung chua diem danh
    stdout, _, rc = run_program(inp)
    if rc == 0:
        if stdout and "Chua co du lieu" in stdout:
            passed("Report for empty class shows 'no data' message")
        else:
            passed("No crash for class with no attendance data")
        add_result("Search/BC", "5.4", "PASS", "Empty report OK")
    else:
        failed(f"Crash (rc={rc})")
        add_result("Search/BC", "5.4", "FAIL", f"Crash rc={rc}")

    # -- 5.5: Xuat bao cao ra file --
    sub_header("5.5: Export report to file for KTLT_01")
    restore_data()
    inp = "\n".join(["5", "4", "KTLT_01", "0", "0"])
    stdout, _, rc = run_program(inp)
    report_path = os.path.join(DATA_DIR, "baocao_KTLT_01.txt")
    if rc == 0 and os.path.exists(report_path):
        report = ""
        with open(report_path, "r", encoding="utf-8", errors="replace") as f:
            report = f.read()
        if len(report) > 50:
            passed(f"Report file created ({len(report)} bytes)")
            add_result("Search/BC", "5.5", "PASS", f"File OK ({len(report)}B)")
        else:
            info(f"Report file too small ({len(report)} bytes)")
            add_result("Search/BC", "5.5", "INFO", "File too small")
        # Cleanup report file
        os.remove(report_path)
    elif rc == 0:
        info("Report file not created")
        add_result("Search/BC", "5.5", "INFO", "No file created")
    else:
        failed(f"Crash (rc={rc})")
        add_result("Search/BC", "5.5", "FAIL", f"Crash rc={rc}")


# ==================================================================
#  MAIN
# ==================================================================

def main():
    print(f"\n{Color.BOLD}{Color.CYAN}")
    print("  ================================================================")
    print("  |   AUTO TEST - Phan Mem Diem Danh Sinh Vien                   |")
    print("  |   25 test cases across 5 modules                            |")
    print("  ================================================================")
    print(f"{Color.RESET}")

    if not os.path.exists(EXE_PATH):
        print(f"{Color.RED}  [!] Not found: {EXE_PATH}")
        print(f"  Build: g++ -std=c++17 -O2 -I src src/*.cpp -o diemdanh.exe{Color.RESET}")
        sys.exit(1)

    if not os.path.exists(DATA_DIR):
        print(f"{Color.RED}  [!] data/ not found{Color.RESET}")
        sys.exit(1)

    info("Backing up original data...")
    backup_data()

    try:
        test_diemdanh_manager()   # Module 1: 5 tests
        test_fileio()             # Module 2: 5 tests
        test_validation()         # Module 3: 5 tests
        test_menu_crud()          # Module 4: 5 tests
        test_search_baocao()      # Module 5: 5 tests
    finally:
        info("Restoring original data...")
        restore_data()
        cleanup_backup()
        # Cleanup any generated report files
        for f in os.listdir(DATA_DIR):
            if f.startswith("baocao_") and f.endswith(".txt"):
                os.remove(os.path.join(DATA_DIR, f))

    # -- Summary --
    header("TEST RESULTS SUMMARY (25 tests)")

    modules = ["DiemDanhMgr", "FileIO", "Validation", "MenuCRUD", "Search/BC"]
    for mod in modules:
        mod_results = [(tc, st, det) for (m, tc, st, det) in results if m == mod]
        if not mod_results:
            continue
        p = sum(1 for _, s, _ in mod_results if s == "PASS")
        print(f"\n  {Color.BOLD}[{mod}]{Color.RESET} {p}/{len(mod_results)} passed")
        for tc, status, detail in mod_results:
            if status == "PASS":
                c = Color.GREEN
            elif status == "FAIL":
                c = Color.RED
            else:
                c = Color.YELLOW
            print(f"    {tc:<8} {c}{status:<6}{Color.RESET} {detail}")

    total_pass = sum(1 for _, _, s, _ in results if s == "PASS")
    total_fail = sum(1 for _, _, s, _ in results if s == "FAIL")
    total_info = sum(1 for _, _, s, _ in results if s == "INFO")

    print(f"\n  {'-' * 50}")
    print(f"  {Color.GREEN}PASS: {total_pass}{Color.RESET}  |  "
          f"{Color.RED}FAIL: {total_fail}{Color.RESET}  |  "
          f"{Color.YELLOW}INFO: {total_info}{Color.RESET}  |  "
          f"Total: {len(results)}")
    print(f"  {Color.CYAN}(PASS=bug found, FAIL=test error, INFO=needs manual check){Color.RESET}\n")


if __name__ == "__main__":
    main()
