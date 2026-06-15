#include "DiemDanhManager.h"
#include "Search.h"
#include "Validation.h"
#include <iostream>
#include <iomanip>
#include <limits>

// ============================================================
//  DiemDanhManager.cpp — Logic nghiệp vụ điểm danh
// ============================================================

namespace DiemDanhManager {

// ── Tính tỷ lệ vắng cho 1 sinh viên ─────────────────────────
// soVang   = đếm phiếu 'P' + 'K' của sv trong lớp
// tiLe     = (float)soVang / tongSoBuoi * 100.0f
// nguyCoiCamThi = (tiLe > 20.0f)
ThongKeSinhVien tinhTiLeVang(Vector<PhieuDiemDanh>& dsDD,
                              SinhVien& sv, int tongSoBuoi) {
    ThongKeSinhVien tk;
    tk.mssv = sv.mssv;
    tk.hoTen = sv.hoTen;
    tk.soVang = 0;
    tk.soVangKhongPhep = 0;

    for (int i = 0; i < (int)dsDD.size(); ++i) {
        if (dsDD[i].mssv == sv.mssv && dsDD[i].maLop == sv.maLop) {
            if (dsDD[i].trangThai == 'P' || dsDD[i].trangThai == 'K') {
                ++tk.soVang;
            }
            if (dsDD[i].trangThai == 'K') {
                ++tk.soVangKhongPhep;
            }
        }
    }

    if (tongSoBuoi > 0) {
        tk.tiLe = (float)tk.soVang / tongSoBuoi * 100.0f;
    } else {
        tk.tiLe = 0.0f;
    }
    tk.nguyCoiCamThi = (tk.tiLe > 20.0f);

    return tk;
}

// ── Ghi điểm danh một buổi cho toàn lớp ─────────────────────
//   1. Lọc SV theo maLop
//   2. Kiểm tra daDiemDanhBuoi() — hỏi xác nhận nếu trùng
//   3. Vòng lặp: in tên SV → nhapTrangThai() → tạo PhieuDiemDanh
//   4. push_back vào dsDD (Menu sẽ gọi FileIO::saveDiemDanh)
void ghiDiemDanhMoiLop(Vector<SinhVien>& dsSV,
                        Vector<PhieuDiemDanh>& dsDD,
                        const String& maLop, const String& ngay) {
    // 1. Lọc sinh viên theo lớp
    Vector<SinhVien> svLop;
    Search::timSinhVienTheoLop(dsSV, maLop, svLop);

    if (svLop.empty()) {
        std::cout << "  [!] Khong co sinh vien nao trong lop "
                  << maLop << ".\n";
        return;
    }

    // 2. Kiểm tra đã điểm danh buổi này chưa
    if (Search::daDiemDanhBuoi(dsDD, ngay, maLop)) {
        std::cout << "  [!] Buoi " << ngay << " da duoc diem danh.\n";
        std::cout << "  Ban co muon diem danh lai? (y/n): ";
        char c;
        std::cin >> c;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (c != 'y' && c != 'Y') return;
    }

    // 3. Vòng lặp nhập trạng thái cho từng SV
    std::cout << "\n  === GHI NHAN DIEM DANH — Lop " << maLop
              << " — Ngay " << ngay << " ===\n\n";

    for (int i = 0; i < (int)svLop.size(); ++i) {
        char tt = Validation::nhapTrangThai(svLop[i].hoTen.c_str());
        PhieuDiemDanh dd;
        dd.mssv = svLop[i].mssv;
        dd.maLop = maLop;
        dd.ngay = ngay;
        dd.trangThai = tt;
        dsDD.push_back(dd);
    }

    std::cout << "  [OK] Da luu diem danh thanh cong! ("
              << (int)svLop.size() << "/" << (int)svLop.size()
              << " sinh vien)\n";
}

// ── Quét toàn lớp, in SV có tỷ lệ vắng > 20% ──────────────
void kiemTraCanhBaoCamThi(Vector<SinhVien>& dsSV,
                           Vector<PhieuDiemDanh>& dsDD,
                           Vector<LopHoc>& dsLop,
                           const String& maLop) {
    // Tìm tổng số buổi
    int tongSoBuoi = 0;
    for (int i = 0; i < (int)dsLop.size(); ++i) {
        if (dsLop[i].maLop == maLop) {
            tongSoBuoi = dsLop[i].tongSoBuoi;
            break;
        }
    }

    std::cout << "\n  === CANH BAO CAM THI — Lop " << maLop << " ===\n\n";
    std::cout << "  " << std::left
              << std::setw(12) << "MSSV"
              << std::setw(25) << "Ho Ten"
              << std::right
              << std::setw(8) << "SoVang"
              << std::setw(8) << "TiLe%"
              << '\n';
    std::cout << "  "
              << "-----------------------------------------------------\n";

    bool found = false;
    for (int i = 0; i < (int)dsSV.size(); ++i) {
        if (dsSV[i].maLop == maLop) {
            ThongKeSinhVien tk = tinhTiLeVang(dsDD, dsSV[i], tongSoBuoi);
            if (tk.nguyCoiCamThi) {
                found = true;
                std::cout << "  " << std::left
                          << std::setw(12) << tk.mssv
                          << std::setw(25) << tk.hoTen
                          << std::right
                          << std::setw(8) << tk.soVang
                          << std::fixed << std::setprecision(1)
                          << std::setw(7) << tk.tiLe << '%'
                          << "  [CANH BAO]\n";
            }
        }
    }

    if (!found) {
        std::cout << "  Khong co sinh vien nao bi canh bao cam thi.\n";
    }
}

// ── Sửa trạng thái 1 phiếu điểm danh ───────────────────────
bool suaDiemDanh(Vector<PhieuDiemDanh>& dsDD,
                  const String& mssv, const String& maLop,
                  const String& ngay, char trangThaiMoi) {
    for (int i = 0; i < (int)dsDD.size(); ++i) {
        if (dsDD[i].mssv == mssv &&
            dsDD[i].maLop == maLop &&
            dsDD[i].ngay == ngay) {
            dsDD[i].trangThai = trangThaiMoi;
            return true;
        }
    }
    return false;
}

} // namespace DiemDanhManager
