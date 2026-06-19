#include "DiemDanhManager.h"
#include "Search.h"
#include "Validation.h"
#include <iostream>
#include <iomanip>

namespace DiemDanhManager {

// Tinh ty le vang cho 1 sinh vien
ThongKeSinhVien tinhTiLeVang(Vector<PhieuDiemDanh>& dsDD,
                             SinhVien& sv, 
                             int tongSoBuoi) {
  ThongKeSinhVien tk;
  tk.mssv = sv.mssv;
  tk.hoTen = sv.hoTen;
  tk.soVang = 0;
  tk.soVangKhongPhep = 0;

  for (int i = 0; i < (int)dsDD.size(); ++i) {
    if (dsDD[i].mssv == sv.mssv && dsDD[i].maLop == sv.maLop) {
      if (dsDD[i].trangThai == TrangThaiDD::VANG_PHEP || dsDD[i].trangThai == TrangThaiDD::VANG_KHONG_PHEP) {
        ++tk.soVang;
      }
      if (dsDD[i].trangThai == TrangThaiDD::VANG_KHONG_PHEP) {
        ++tk.soVangKhongPhep;
      }
    }
  }

  if (tongSoBuoi > 0) {
    tk.tiLe = static_cast<float>(tk.soVangKhongPhep) / static_cast<float>(tongSoBuoi) * 100.0f;
  } else {
    tk.tiLe = 0.0f;
  }
  tk.nguyCoCamThi = (tk.tiLe > 20.0f);

  return tk;
}

// Ghi diem danh mot buoi cho toan lop
void ghiDiemDanhMoiLop(Vector<SinhVien>& dsSV,
                       Vector<PhieuDiemDanh>& dsDD,
                       const String& maLop, 
                       const String& ngay) {
  Vector<SinhVien> svLop;
  Search::timSinhVienTheoLop(dsSV, maLop, svLop);

  if (svLop.empty()) {
    std::cout << "  [!] Khong co sinh vien nao trong lop " << maLop << ".\n";
    return;
  }

  if (Search::daDiemDanhBuoi(dsDD, ngay, maLop)) {
    std::cout << "  [!] Buoi " << ngay << " da duoc diem danh.\n";
    if (!Validation::nhapXacNhan("  Ban co muon diem danh lai?")) return;
  }

  std::cout << "\n  === GHI NHAN DIEM DANH — Lop " << maLop
            << " — Ngay " << ngay << " ===\n\n";

  for (int i = 0; i < (int)svLop.size(); ++i) {
    TrangThaiDD tt = Validation::nhapTrangThai(svLop[i].hoTen.c_str());
    PhieuDiemDanh dd;
    dd.mssv = svLop[i].mssv;
    dd.maLop = maLop;
    dd.ngay = ngay;
    dd.trangThai = tt;
    dsDD.push_back(dd);
  }

  std::cout << "  [OK] Da luu diem danh thanh cong! ("
            << (int)svLop.size() << "/" << (int)svLop.size() << " sinh vien)\n";
}

// Quet toan lop, in SV co ty le vang > 20%
void kiemTraCanhBaoCamThi(Vector<SinhVien>& dsSV,
                          Vector<PhieuDiemDanh>& dsDD,
                          Vector<LopHoc>& dsLop,
                          const String& maLop) {
  int tongSoBuoi = 0;
  for (int i = 0; i < (int)dsLop.size(); ++i) {
    if (dsLop[i].maLop == maLop) {
      tongSoBuoi = dsLop[i].tongSoBuoi;
      break;
    }
  }

  std::cout << "\n  === CANH BAO CAM THI — Lop " << maLop << " ===\n\n";
  std::cout << "  " << std::left << std::setw(12) << "MSSV"
            << std::setw(25) << "Ho Ten"
            << std::right << std::setw(8) << "SoVang"
            << std::setw(8) << "TiLe%" << "\n";
  std::cout << "  -----------------------------------------------------\n";

  bool found = false;
  for (int i = 0; i < (int)dsSV.size(); ++i) {
    if (dsSV[i].maLop == maLop) {
      ThongKeSinhVien tk = tinhTiLeVang(dsDD, dsSV[i], tongSoBuoi);
      if (tk.nguyCoCamThi) {
        found = true;
        std::cout << "  " << std::left << std::setw(12) << tk.mssv
                  << std::setw(25) << tk.hoTen
                  << std::right << std::setw(8) << tk.soVang
                  << std::fixed << std::setprecision(1) << std::setw(7) << tk.tiLe << '%'
                  << "  [CANH BAO]\n";
      }
    }
  }
// comment lai o day ti bo sung them phan cot canh bao?
  if (!found) {
    std::cout << "  Khong co sinh vien nao bi canh bao cam thi.\n";
  }
}

// Sua trang thai 1 phieu diem danh
bool suaDiemDanh(Vector<PhieuDiemDanh>& dsDD,
                  const String& mssv, 
                  const String& maLop,
                  const String& ngay, 
                  TrangThaiDD trangThaiMoi) {
  for (int i = 0; i < (int)dsDD.size(); ++i) {
    if (dsDD[i].mssv == mssv && dsDD[i].maLop == maLop && dsDD[i].ngay == ngay) {
      dsDD[i].trangThai = trangThaiMoi;
      return true;
    }
  }
  return false;
}

} // namespace DiemDanhManager
