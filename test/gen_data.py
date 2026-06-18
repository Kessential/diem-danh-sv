# gen_data.py - Generate sample data for Diem Danh app
# Run: python test/gen_data.py  (from project root)
# Output: data/lophoc.txt, data/sinhvien.txt, data/diemdanh.txt

import os
import random

PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(PROJECT_DIR, "data")

# -- 50 classes (4 original + 46 new) --
CLASSES = [
    # 4 lop goc
    ("KTLT_01", "Ky thuat lap trinh",         "Nguyen Van An",      3, 1, 4, "B4-201", 15),
    ("CSDL_01", "Co so du lieu",               "Tran Thi Binh",      5, 5, 4, "A1-101", 15),
    ("MMT_01",  "Mang may tinh",               "Le Van Cuong",       2, 3, 3, "D5-102", 12),
    ("CTDL_01", "Cau truc du lieu",            "Pham Minh Duc",      4, 7, 4, "D7-307", 15),
    # 46 lop moi
    ("KTLT_02", "Ky thuat lap trinh",         "Hoang Thanh Tung",   4, 1, 4, "B4-202", 15),
    ("KTLT_03", "Ky thuat lap trinh",         "Vo Minh Hieu",       5, 3, 4, "B4-203", 15),
    ("CSDL_02", "Co so du lieu",               "Nguyen Thi Lan",     3, 5, 4, "A1-102", 15),
    ("CSDL_03", "Co so du lieu",               "Bui Van Hai",        2, 1, 4, "A1-103", 12),
    ("MMT_02",  "Mang may tinh",               "Phan Duc Long",      4, 3, 3, "D5-201", 12),
    ("MMT_03",  "Mang may tinh",               "Truong Thi Mai",     6, 5, 3, "D5-202", 12),
    ("CTDL_02", "Cau truc du lieu",            "Do Quoc Bao",        2, 7, 4, "D7-308", 15),
    ("CTDL_03", "Cau truc du lieu",            "Ly Van Khoa",        5, 1, 4, "D7-309", 15),
    ("HDH_01",  "He dieu hanh",                "Le Thi Huong",       3, 3, 3, "C2-101", 12),
    ("HDH_02",  "He dieu hanh",                "Ngo Van Thanh",      4, 5, 3, "C2-102", 12),
    ("HDH_03",  "He dieu hanh",                "Dang Minh Tri",      6, 1, 3, "C2-103", 12),
    ("TCC_01",  "Toan cao cap",                "Dinh Thi Ngoc",      2, 1, 4, "A2-201", 15),
    ("TCC_02",  "Toan cao cap",                "Luu Van Phat",       3, 5, 4, "A2-202", 15),
    ("TCC_03",  "Toan cao cap",                "Mai Hoang Nam",      5, 1, 4, "A2-203", 15),
    ("XSTK_01", "Xac suat thong ke",          "Vu Thi Thu",         4, 3, 3, "A3-101", 12),
    ("XSTK_02", "Xac suat thong ke",          "Hoang Van Dat",      2, 7, 3, "A3-102", 12),
    ("XSTK_03", "Xac suat thong ke",          "Pham Duc Huy",       6, 1, 3, "A3-103", 12),
    ("VLDC_01", "Vat ly dai cuong",            "Tran Van Son",       3, 1, 3, "B1-101", 12),
    ("VLDC_02", "Vat ly dai cuong",            "Nguyen Thi Hanh",    5, 3, 3, "B1-102", 12),
    ("CNPM_01", "Cong nghe phan mem",          "Le Quoc Anh",        2, 1, 4, "C3-201", 15),
    ("CNPM_02", "Cong nghe phan mem",          "Phan Thi Vy",        4, 5, 4, "C3-202", 15),
    ("CNPM_03", "Cong nghe phan mem",          "Huynh Van Lam",      6, 1, 4, "C3-203", 15),
    ("TTNT_01", "Tri tue nhan tao",            "Do Minh Khoi",       3, 7, 4, "D1-101", 15),
    ("TTNT_02", "Tri tue nhan tao",            "Bui Thi Trang",      5, 1, 4, "D1-102", 15),
    ("LTUD_01", "Lap trinh ung dung",          "Vo Van Phuc",        2, 3, 4, "B2-301", 15),
    ("LTUD_02", "Lap trinh ung dung",          "Truong Duc Tai",     4, 1, 4, "B2-302", 15),
    ("LTUD_03", "Lap trinh ung dung",          "Nguyen Hoang Vu",    6, 5, 4, "B2-303", 15),
    ("ATTT_01", "An toan thong tin",           "Tran Minh Nhat",     3, 5, 3, "C4-101", 12),
    ("ATTT_02", "An toan thong tin",           "Le Thi Quynh",       5, 7, 3, "C4-102", 12),
    ("PTDL_01", "Phan tich du lieu",           "Pham Van Trung",     2, 1, 3, "D2-201", 12),
    ("PTDL_02", "Phan tich du lieu",           "Hoang Thi Nhi",      4, 3, 3, "D2-202", 12),
    ("LTWEB_01","Lap trinh web",               "Dang Quoc Vinh",     3, 1, 4, "B3-101", 15),
    ("LTWEB_02","Lap trinh web",               "Ngo Thi Phuong",     5, 5, 4, "B3-102", 15),
    ("LTWEB_03","Lap trinh web",               "Dinh Van Hieu",      2, 1, 4, "B3-103", 15),
    ("DTDM_01", "Dien toan dam may",           "Mai Thi Thao",       4, 7, 3, "D3-101", 12),
    ("DTDM_02", "Dien toan dam may",           "Luu Duc Thinh",      6, 1, 3, "D3-102", 12),
    ("TKHT_01", "Thiet ke he thong",           "Vu Van Long",        3, 3, 4, "C1-201", 15),
    ("TKHT_02", "Thiet ke he thong",           "Bui Thi Yen",        5, 1, 4, "C1-202", 15),
    ("NMLT_01", "Nhap mon lap trinh",          "Do Van Kien",        2, 5, 4, "A4-101", 15),
    ("NMLT_02", "Nhap mon lap trinh",          "Ho Thi Linh",        4, 1, 4, "A4-102", 15),
    ("NMLT_03", "Nhap mon lap trinh",          "Phan Minh Tien",     6, 3, 4, "A4-103", 15),
    ("DTHS_01", "Do thi va hoc sau",           "Huynh Quoc Dat",     3, 7, 3, "D4-101", 12),
    ("DTHS_02", "Do thi va hoc sau",           "Ly Thi Uyen",        5, 3, 3, "D4-102", 12),
    ("LTMB_01", "Lap trinh mobile",            "Truong Van Son",     2, 1, 4, "B5-101", 15),
    ("LTMB_02", "Lap trinh mobile",            "Nguyen Thi My",      4, 5, 4, "B5-102", 15),
    ("LTMB_03", "Lap trinh mobile",            "Vu Quoc Tuan",       6, 1, 4, "B5-103", 15),
]

# -- Vietnamese name parts (no diacritics) - expanded for ~2500 unique names --
HO = [
    "Nguyen", "Tran", "Le", "Pham", "Hoang", "Huynh", "Phan",
    "Vu", "Vo", "Dang", "Bui", "Do", "Ho", "Ngo", "Duong",
    "Ly", "Truong", "Dinh", "Luu", "Mai", "Trinh", "Ta",
    "Cao", "Ha", "Luong", "Dam", "To", "Chau",
]
DEM = [
    "Van", "Thi", "Minh", "Quoc", "Hoang", "Ngoc", "Thanh",
    "Duc", "Xuan", "Huu", "Bao", "Duy", "Khanh", "Anh", "Phuong",
    "Gia", "Dinh", "Cong", "Kim", "Hong", "Trong",
]
TEN = [
    "An", "Binh", "Cuong", "Dung", "Em", "Phong", "Giang", "Hoa",
    "Hung", "Kien", "Linh", "Minh", "Nam", "Oanh", "Phat",
    "Quang", "Rang", "Son", "Tuan", "Uyen", "Vinh", "Xuan",
    "Yen", "Trang", "Hieu", "Khoa", "Long", "Ngoc", "Phuc",
    "Tai", "Thao", "Thinh", "Tien", "Trung", "Vy", "Huy",
    "Dat", "Nhat", "Bao", "Hanh", "Lam", "My",
    "Nhi", "Quynh", "Thu", "Tuyen", "Vu", "Dung",
    "Sang", "Tan", "Khang", "Loc", "Phong", "Tam", "Tri",
    "Hao", "Quan", "Thang", "Luan", "Khai", "Hien", "Ngan",
]

# -- Dates for attendance --
DATES = [
    "01/09/2025", "08/09/2025", "15/09/2025", "22/09/2025",
    "29/09/2025", "06/10/2025", "13/10/2025", "20/10/2025",
    "27/10/2025", "03/11/2025", "10/11/2025", "17/11/2025",
    "24/11/2025", "01/12/2025", "08/12/2025",
]

def gen_name():
    return f"{random.choice(HO)} {random.choice(DEM)} {random.choice(TEN)}"

def gen_status():
    # 80% co mat, 10% vang phep, 10% vang khong phep
    r = random.random()
    if r < 0.80:
        return "C"
    elif r < 0.90:
        return "P"
    else:
        return "K"

def main():
    os.makedirs(DATA_DIR, exist_ok=True)
    random.seed(42)  # Reproducible

    # -- Generate lophoc.txt --
    with open(os.path.join(DATA_DIR, "lophoc.txt"), "w", encoding="utf-8") as f:
        for ma, ten, gv, thu, tiet, sotiet, phong, buoi in CLASSES:
            f.write(f"{ma}|{ten}|{gv}|{thu}|{tiet}|{sotiet}|{phong}|{buoi}\n")
    print(f"  [OK] lophoc.txt: {len(CLASSES)} classes")

    # -- Generate sinhvien.txt --
    all_students = []
    mssv_counter = 22010001
    students_per_class = [random.randint(48, 50) for _ in CLASSES]

    used_names = set()
    with open(os.path.join(DATA_DIR, "sinhvien.txt"), "w", encoding="utf-8") as f:
        for i, (ma_lop, _, _, _, _, _, _, _) in enumerate(CLASSES):
            n = students_per_class[i]
            for j in range(n):
                mssv = str(mssv_counter)
                mssv_counter += 1
                # Ensure unique names
                name = gen_name()
                while name in used_names:
                    name = gen_name()
                used_names.add(name)
                f.write(f"{mssv}|{name}|{ma_lop}\n")
                all_students.append((mssv, ma_lop))
    total_sv = len(all_students)
    print(f"  [OK] sinhvien.txt: {total_sv} students ({', '.join(str(x) for x in students_per_class)} per class)")

    # -- Generate diemdanh.txt --
    # Moi lop diem danh so buoi tuong ung voi tongSoBuoi
    record_count = 0
    with open(os.path.join(DATA_DIR, "diemdanh.txt"), "w", encoding="utf-8") as f:
        for i, (ma_lop, _, _, _, _, _, _, buoi) in enumerate(CLASSES):
            # Lay danh sach SV cua lop nay
            lop_students = [(m, ml) for m, ml in all_students if ml == ma_lop]
            # Diem danh so buoi = min(buoi, len(DATES))
            num_dates = min(buoi, len(DATES))
            for d in range(num_dates):
                date = DATES[d]
                for mssv, _ in lop_students:
                    status = gen_status()
                    f.write(f"{mssv}|{ma_lop}|{date}|{status}\n")
                    record_count += 1
    print(f"  [OK] diemdanh.txt: {record_count} attendance records")
    print(f"\n  Total: {len(CLASSES)} classes, {total_sv} students, {record_count} records")

if __name__ == "__main__":
    print("\n  === Generate Sample Data ===\n")
    main()
    print("\n  Done! Run .\\diemdanh.exe to see the data.\n")
