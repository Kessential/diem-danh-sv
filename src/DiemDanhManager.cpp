#include "DiemDanhManager.h"
#include "Menu.h"
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
    tk.tiLeVangKP   = static_cast<float>(tk.soVangKhongPhep) / static_cast<float>(tongSoBuoi) * 100.0f;
    tk.tiLeVangTong = static_cast<float>(tk.soVang)          / static_cast<float>(tongSoBuoi) * 100.0f;
  } else {
    tk.tiLeVangKP   = 0.0f;
    tk.tiLeVangTong = 0.0f;
  }

  bool dieuKienA = (tk.tiLeVangKP   >= 20.0f); // Vang K.phep >= 20%
  bool dieuKienB = (tk.tiLeVangTong >= 30.0f); // Tong vang   >= 30%
  tk.nguyCoCamThi = dieuKienA || dieuKienB;

  if      (dieuKienA && dieuKienB) tk.lyDo = 3;
  else if (dieuKienA)              tk.lyDo = 1;
  else if (dieuKienB)              tk.lyDo = 2;
  else                             tk.lyDo = 0;

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

// Quet toan lop, in SV co ty le vang khong phep >= 20% HOAC tong vang >= 30%
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
  std::cout << "  Dieu kien canh bao:\n";
  std::cout << "    (A) Vang khong phep >= 20% tong so buoi\n";
  std::cout << "    (B) Tong vang       >= 30% tong so buoi\n\n";

  // separator(93) + prefix 2 = 95 ky tu/dong
  printDynamicSeparator(93);
  std::cout << "  " << std::left  << std::setw(12) << "MSSV"
                    << std::setw(22) << "Ho Ten"
            << std::right << std::setw(9)  << "TongVang"
                          << std::setw(8)  << "VangKP"
                          << std::setw(9)  << "TiLeKP%"
                          << std::setw(10) << "TiLeTong%"
                          << "  Ly do\n";
  printDynamicSeparator(93);

  bool found = false;
  int demCanhBao = 0;
  for (int i = 0; i < (int)dsSV.size(); ++i) {
    if (dsSV[i].maLop == maLop) {
      ThongKeSinhVien tk = tinhTiLeVang(dsDD, dsSV[i], tongSoBuoi);
      if (tk.nguyCoCamThi) {
        found = true;
        ++demCanhBao;
        String lyDoStr = (tk.lyDo == 3) ? String("[KP>=20% & Tong>=30%]")
                       : (tk.lyDo == 1) ? String("[Vang KP>=20%]")
                                        : String("[Tong vang>=30%]");
        std::cout << "  " << std::left  << std::setw(12) << tk.mssv
                          << std::setw(22) << tk.hoTen
                  << std::right << std::setw(9)  << tk.soVang
                                << std::setw(8)  << tk.soVangKhongPhep
                  << std::fixed << std::setprecision(1)
                                << std::setw(8)  << tk.tiLeVangKP   << "%"
                                << std::setw(9)  << tk.tiLeVangTong << "%"
                  << "  " << lyDoStr << "\n";
      }
    }
  }
  printDynamicSeparator(93);
  if (!found) {
    std::cout << "  [I] Khong co sinh vien nao bi canh bao cam thi.\n";
  } else {
    std::cout << "\n  [!] Co " << demCanhBao << " sinh vien bi canh bao cam thi.\n";
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
