#include "Menu.h"
#include "Validation.h"
#include "Sort.h"
#include <iostream>
#include <iomanip>

// --- Cac ham ho tro (Helpers) ---
static void tachTen(const String& hoTen, String& hoDem, String& ten) {
  int len = hoTen.length();
  int lastSpace = -1;
  for (int i = len - 1; i >= 0; --i) {
    if (hoTen[i] == ' ') {
      lastSpace = i;
      break;
    }
  }
  if (lastSpace == -1) {
    hoDem = "";
    ten = hoTen;
  } else {
    hoDem = hoTen.substring(0, lastSpace);
    ten = hoTen.substring(lastSpace + 1, len - lastSpace - 1);
  }
}

static long long parseDate(const String& dateStr) {
  if (dateStr.length() < 10) return 0;
  int dd = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
  int mm = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
  int yyyy = (dateStr[6] - '0') * 1000 + (dateStr[7] - '0') * 100 +
             (dateStr[8] - '0') * 10 + (dateStr[9] - '0');
  return (long long)yyyy * 10000 + mm * 100 + dd;
}

void printHeader(const char *title) {
  std::cout << "\n";
  std::cout << "  ╔══════════════════════════════════════════════╗\n";
  std::cout << "  ║  " << std::left << std::setw(44) << title << "║\n";
  std::cout << "  ╚══════════════════════════════════════════════╝\n";
}

void printSeparator() {
  std::cout << "  ────────────────────────────────────────────────\n";
}

void printDynamicSeparator(int width) {
  std::cout << "  ";
  for (int i = 0; i < width; ++i) {
    std::cout << "─";
  }
  std::cout << "\n";
}

// --- Quan ly Lop hoc ---
void hienThiDanhSachLop(const Vector<LopHoc> &dsLop) {
  printDynamicSeparator(88);
  if (dsLop.size() == 0) {
    std::cout << "  [I] Chua co lop hoc nao.\n";
    return;
  }
  std::cout << "  " << std::left << std::setw(4)  << "STT"
            << std::setw(10) << "Ma Lop"
            << std::setw(25) << "Ten HP"
            << std::setw(17) << "Giang Vien"
            << std::right << std::setw(4) << "Thu"
            << std::setw(7) << "TietBD"
            << std::setw(6) << "STiet"
            << std::left << " " << std::setw(8) << "Phong"
            << std::right << std::setw(6) << "SBuoi" << "\n";
  printDynamicSeparator(88);
  for (int i = 0; i < (int)dsLop.size(); ++i) {
    const LopHoc &lh = dsLop[i];
    std::cout << "  " << std::left << std::setw(4)  << (i + 1)
              << std::setw(10) << lh.maLop
              << std::setw(25) << lh.tenLop
              << std::setw(17) << lh.giangVien
              << std::right << std::setw(4) << lh.tkb.thu
              << std::setw(7) << lh.tkb.tietBatDau
              << std::setw(6) << lh.tkb.soTiet
              << std::left << " " << std::setw(8) << lh.tkb.phong
              << std::right << std::setw(6) << lh.tongSoBuoi << "\n";
  }
  printDynamicSeparator(88);
}

void themLopHoc(Vector<LopHoc> &dsLop, const char* pathLop) {
  LopHoc lh;
  std::cout << "\n  ─── THEM LOP HOC MOI ───\n";
  while (true) {
    Validation::nhapChuoi("  Ma lop", lh.maLop);
    if (Validation::isValidMaLop(lh.maLop)) break;
    std::cout << "  [!] Ma lop khong hop le.\n";
  }
  if (Search::timLopHocTheoMa(dsLop, lh.maLop) != -1) {
    std::cout << "  [!] Ma lop '" << lh.maLop << "' da ton tai!\n";
    return;
  }
  Validation::nhapChuoi("  Ten mon hoc", lh.tenLop);
  Validation::nhapChuoi("  Giang vien", lh.giangVien);
  lh.tkb.thu = Validation::nhapSoNguyen("  Thu (2-7)", 2, 7);
  lh.tkb.tietBatDau = Validation::nhapSoNguyen("  Tiet bat dau (1-12)", 1, 12);
  lh.tkb.soTiet = Validation::nhapSoNguyen("  So tiet", 1, 6);
  Validation::nhapChuoi("  Phong hoc", lh.tkb.phong);
  lh.tongSoBuoi = Validation::nhapSoNguyen("  Tong so buoi", 1, 60);
  dsLop.push_back(lh);
  FileIO::saveLopHoc(pathLop, dsLop);
  std::cout << "  [OK] Da them lop '" << lh.maLop << "'.\n";
}

void suaLopHoc(Vector<LopHoc> &dsLop, const char* pathLop) {
  String maLop;
  std::cout << "\n  ─── SUA THONG TIN LOP HOC ───\n";
  Validation::nhapChuoi("  Ma lop can sua", maLop);
  int idx = Search::timLopHocTheoMa(dsLop, maLop);
  if (idx == -1) {
    std::cout << "  [!] Khong tim thay lop '" << maLop << "'.\n";
    return;
  }
  LopHoc &lh = dsLop[idx];
  std::cout << "  (De trong de giu nguyen gia tri hien tai)\n";
  Validation::nhapChuoiCoBaoLuu("  Ten mon hoc moi", lh.tenLop);
  Validation::nhapChuoiCoBaoLuu("  Giang vien moi", lh.giangVien);
  Validation::nhapSoNguyenCoBaoLuu("  Thu (2-7)", lh.tkb.thu, 2, 7);
  Validation::nhapSoNguyenCoBaoLuu("  Tiet bat dau", lh.tkb.tietBatDau, 1, 12);
  Validation::nhapSoNguyenCoBaoLuu("  So tiet", lh.tkb.soTiet, 1, 6);
  Validation::nhapChuoiCoBaoLuu("  Phong hoc", lh.tkb.phong);
  Validation::nhapSoNguyenCoBaoLuu("  Tong so buoi", lh.tongSoBuoi, 1, 60);
  FileIO::saveLopHoc(pathLop, dsLop);
  std::cout << "  [OK] Da cap nhat lop '" << maLop << "'.\n";
}

void xoaLopHoc(Vector<LopHoc> &dsLop, 
               Vector<SinhVien>& dsSV, 
               Vector<PhieuDiemDanh>& dsDD, 
               const char* pathLop, 
               const char* pathSV, 
               const char* pathDD) {
  String maLop;
  std::cout << "\n  ─── XOA LOP HOC ───\n";
  Validation::nhapChuoi("  Ma lop can xoa", maLop);
  int idx = Search::timLopHocTheoMa(dsLop, maLop);
  if (idx == -1) {
    std::cout << "  [!] Khong tim thay lop '" << maLop << "'.\n";
    return;
  }
  
  int countSV = 0;
  for (int i = 0; i < (int)dsSV.size(); ++i) {
    if (dsSV[i].maLop == maLop) countSV++;
  }
  int countDD = 0;
  for (int i = 0; i < (int)dsDD.size(); ++i) {
    if (dsDD[i].maLop == maLop) countDD++;
  }

  if (countSV > 0 || countDD > 0) {
    std::cout << "  [!] Lop hoc nay dang co " << countSV << " sinh vien va " << countDD << " phieu diem danh.\n";
    if (!Validation::nhapXacNhan("  Ban co chac chan muon xoa (moi du lieu lien quan se bi mat)?")) {
      std::cout << "  [I] Da huy thao tac xoa.\n";
      return;
    }
  }

  for (int i = (int)dsDD.size() - 1; i >= 0; --i) {
    if (dsDD[i].maLop == maLop) {
      dsDD.remove(i);
    }
  }
  for (int i = (int)dsSV.size() - 1; i >= 0; --i) {
    if (dsSV[i].maLop == maLop) {
      dsSV.remove(i);
    }
  }

  dsLop.remove(idx);
  FileIO::saveDiemDanh(pathDD, dsDD);
  FileIO::saveSinhVien(pathSV, dsSV);
  FileIO::saveLopHoc(pathLop, dsLop);
  std::cout << "  [OK] Da xoa lop '" << maLop << "' va tat ca du lieu lien quan.\n";
}

void menuQuanLyLopHoc(Vector<LopHoc> &dsLop, 
                      Vector<SinhVien>& dsSV, 
                      Vector<PhieuDiemDanh>& dsDD, 
                      const char* pathLop, 
                      const char* pathSV, 
                      const char* pathDD) {
  int choice;
  do {
    printHeader("1. QUAN LY LOP HOC");
    std::cout << "    1. Xem danh sach lop hoc\n";
    std::cout << "    2. Them lop hoc moi\n";
    std::cout << "    3. Sua thong tin lop hoc\n";
    std::cout << "    4. Xoa lop hoc\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 4);
    switch (choice) {
    case 1:
      hienThiDanhSachLop(dsLop);
      break;
    case 2:
      themLopHoc(dsLop, pathLop);
      break;
    case 3:
      suaLopHoc(dsLop, pathLop);
      break;
    case 4:
      xoaLopHoc(dsLop, dsSV, dsDD, pathLop, pathSV, pathDD);
      break;
    }
  } while (choice != 0);
}

// --- Quan ly Sinh vien ---
void hienThiSVTheoLop(const Vector<SinhVien> &dsSV, const String &maLop) {
  std::cout << "\n  Danh sach sinh vien lop " << maLop << ":\n";
  printDynamicSeparator(41);
  std::cout << "  " << std::left << std::setw(4)  << "STT"
            << std::setw(12) << "MSSV"
            << std::setw(25) << "Ho Ten" << "\n";
  printDynamicSeparator(41);
  int count = 0;
  for (int i = 0; i < (int)dsSV.size(); ++i) {
    if (dsSV[i].maLop == maLop) {
      std::cout << "  " << std::left << std::setw(4)  << (count + 1)
                << std::setw(12) << dsSV[i].mssv
                << std::setw(25) << dsSV[i].hoTen << "\n";
      ++count;
    }
  }
  if (count == 0)
    std::cout << "  [I] Khong co sinh vien nao.\n";
  else {
    printDynamicSeparator(41);
    std::cout << "\n  [I] Tong cong: " << count << " sinh vien.\n";
  }
}

void themSinhVien(Vector<SinhVien> &dsSV, 
                  Vector<LopHoc> &dsLop, 
                  const char* pathSV) {
  SinhVien sv;
  std::cout << "\n  ─── THEM SINH VIEN ───\n";
  Validation::nhapChuoi("  MSSV", sv.mssv);
  if (!Validation::isValidMSSV(sv.mssv)) {
    std::cout << "  [!] MSSV khong hop le.\n";
    return;
  }
  if (Search::timSinhVienTheoMSSV(dsSV, sv.mssv) != -1) {
    std::cout << "  [!] MSSV '" << sv.mssv << "' da ton tai!\n";
    return;
  }
  Validation::nhapChuoi("  Ho Ten", sv.hoTen);
  while (true) {
    Validation::nhapChuoi("  Ma Lop", sv.maLop);
    if (Validation::isValidMaLop(sv.maLop)) break;
    std::cout << "  [!] Ma lop khong hop le.\n";
  }
  if (Search::timLopHocTheoMa(dsLop, sv.maLop) == -1) {
    std::cout << "  [!] Ma lop '" << sv.maLop << "' khong ton tai!\n";
    return;
  }
  dsSV.push_back(sv);
  FileIO::saveSinhVien(pathSV, dsSV);
  std::cout << "  [OK] Da them sinh vien '" << sv.mssv << "'.\n";
}

void suaSinhVien(Vector<SinhVien> &dsSV, const char* pathSV) {
  String mssv;
  std::cout << "\n  ─── SUA THONG TIN SINH VIEN ───\n";
  Validation::nhapChuoi("  MSSV can sua", mssv);
  int idx = Search::timSinhVienTheoMSSV(dsSV, mssv);
  if (idx == -1) {
    std::cout << "  [!] Khong tim thay MSSV '" << mssv << "'.\n";
    return;
  }
  std::cout << "  (De trong de giu nguyen gia tri hien tai)\n";
  Validation::nhapChuoiCoBaoLuu("  Ho Ten moi", dsSV[idx].hoTen);
  FileIO::saveSinhVien(pathSV, dsSV);
  std::cout << "  [OK] Da cap nhat sinh vien '" << mssv << "'.\n";
}

void xoaSinhVien(Vector<SinhVien> &dsSV, 
                 Vector<PhieuDiemDanh>& dsDD, 
                 const char* pathSV, 
                 const char* pathDD) {
  String mssv;
  std::cout << "\n  ─── XOA SINH VIEN ───\n";
  Validation::nhapChuoi("  MSSV can xoa", mssv);
  int idx = Search::timSinhVienTheoMSSV(dsSV, mssv);
  if (idx == -1) {
    std::cout << "  [!] Khong tim thay MSSV '" << mssv << "'.\n";
    return;
  }

  int countDD = 0;
  for (int i = 0; i < (int)dsDD.size(); ++i) {
    if (dsDD[i].mssv == mssv) countDD++;
  }

  if (countDD > 0) {
    std::cout << "  [!] Sinh vien nay dang co " << countDD << " phieu diem danh.\n";
    if (!Validation::nhapXacNhan("  Ban co chac chan muon xoa (moi du lieu lien quan se bi mat)?")) {
      std::cout << "  [I] Da huy thao tac xoa.\n";
      return;
    }
  }

  for (int i = (int)dsDD.size() - 1; i >= 0; --i) {
    if (dsDD[i].mssv == mssv) {
      dsDD.remove(i);
    }
  }

  dsSV.remove(idx);
  FileIO::saveDiemDanh(pathDD, dsDD);
  FileIO::saveSinhVien(pathSV, dsSV);
  std::cout << "  [OK] Da xoa sinh vien '" << mssv << "' va tat ca du lieu lien quan.\n";
}

void menuQuanLySinhVien(Vector<SinhVien> &dsSV, 
                        Vector<LopHoc> &dsLop, 
                        Vector<PhieuDiemDanh>& dsDD,
                        const char* pathSV,
                        const char* pathDD) {
  int choice;
  do {
    printHeader("2. QUAN LY SINH VIEN");
    std::cout << "    1. Xem danh sach SV theo lop\n";
    std::cout << "    2. Them sinh vien vao lop\n";
    std::cout << "    3. Sua thong tin sinh vien\n";
    std::cout << "    4. Xoa sinh vien khoi lop\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 4);
    switch (choice) {
    case 1: {
      String maLop;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
      } else {
        hienThiSVTheoLop(dsSV, maLop);
      }
      break;
    }
    case 2:
      themSinhVien(dsSV, dsLop, pathSV);
      break;
    case 3:
      suaSinhVien(dsSV, pathSV);
      break;
    case 4:
      xoaSinhVien(dsSV, dsDD, pathSV, pathDD);
      break;
    }
  } while (choice != 0);
}

// --- Diem danh ---
void menuDiemDanh(Vector<LopHoc> &dsLop, 
                  Vector<SinhVien> &dsSV,
                  Vector<PhieuDiemDanh> &dsDD,
                  const char* pathDD) {
  int choice;
  do {
    printHeader("3. DIEM DANH");
    std::cout << "    1. Ghi nhan diem danh buoi hoc moi\n";
    std::cout << "    2. Xem/Sua diem danh theo ngay + lop\n";
    std::cout << "    3. Kiem tra canh bao cam thi (ca lop)\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 3);
    switch (choice) {
    case 1: {
      String maLop, ngay;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        break;
      }
      while (true) {
        Validation::nhapChuoi("  Ngay diem danh (DD/MM/YYYY)", ngay);
        if (Validation::isValidDate(ngay))
          break;
        std::cout << "  [!] Ngay khong hop le hoac sai dinh dang. Vui long nhap lai.\n";
      }
      DiemDanhManager::ghiDiemDanhMoiLop(dsSV, dsDD, maLop, ngay);
      FileIO::saveDiemDanh(pathDD, dsDD);
      break;
    }
    case 2: {
      String maLop, ngay;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        break;
      }
      while (true) {
        Validation::nhapChuoi("  Ngay (DD/MM/YYYY)", ngay);
        if (Validation::isValidDate(ngay))
          break;
        std::cout << "  [!] Ngay khong hop le hoac sai dinh dang. Vui long nhap lai.\n";
      }
      Vector<PhieuDiemDanh> result;
      Search::timDiemDanhTheoNgayVaLop(dsDD, ngay, maLop, result);
      if (result.size() == 0) {
        std::cout << "  [I] Khong co du lieu diem danh ngay " << ngay << " lop " << maLop << ".\n";
        break;
      }
      printDynamicSeparator(61);
      std::cout << "  " << std::left << std::setw(4)  << "STT"
                << std::setw(12) << "MSSV"
                << std::setw(30) << "Ho Ten"
                << "Trang thai\n";
      printDynamicSeparator(61);
      for (int i = 0; i < (int)result.size(); ++i) {
        int idx = Search::timSinhVienTheoMSSV(dsSV, result[i].mssv);
        // Kiem tra ton tai SV. Toan tu tam phan tren String de dong nhat
        String ten = (idx >= 0) ? dsSV[idx].hoTen : String("?");
        String ttStr = result[i].trangThai == TrangThaiDD::CO_MAT   ? String("Co mat")
                     : result[i].trangThai == TrangThaiDD::VANG_PHEP ? String("Vang co phep")
                                                                  : String("Vang khong phep");
        std::cout << "  " << std::left << std::setw(4)  << (i + 1)
                  << std::setw(12) << result[i].mssv
                  << std::setw(30) << ten
                  << ttStr << "\n";
      }
      printDynamicSeparator(61);
      if (Validation::nhapXacNhan("\n  Ban co muon sua diem danh?")) {
        String mssv;
        Validation::nhapChuoi("  MSSV can sua", mssv);
        // Kiem tra MSSV co phieu diem danh trong buoi nay khong
        Vector<PhieuDiemDanh> check;
        Search::timDiemDanhTheoMSSVvaLop(dsDD, mssv, maLop, check);
        bool mssvTonTai = false;
        for (int i = 0; i < (int)check.size(); ++i) {
          if (check[i].ngay == ngay) { mssvTonTai = true; break; }
        }
        if (!mssvTonTai) {
          std::cout << "  [!] MSSV '" << mssv << "' khong co trong danh sach diem danh buoi nay.\n";
        } else {
          TrangThaiDD ttMoi = Validation::nhapTrangThai(mssv.c_str());
          if (DiemDanhManager::suaDiemDanh(dsDD, mssv, maLop, ngay, ttMoi)) {
            FileIO::saveDiemDanh(pathDD, dsDD);
            std::cout << "  [OK] Da cap nhat diem danh.\n";
          } else {
            std::cout << "  [!] Khong tim thay phieu diem danh.\n";
          }
        }
      }
      break;
    }
    case 3: {
      String maLop;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        break;
      }
      DiemDanhManager::kiemTraCanhBaoCamThi(dsSV, dsDD, dsLop, maLop);
      break;
    }
    }
  } while (choice != 0);
}

// --- Tim kiem ---
void menuTimKiem(Vector<LopHoc> &dsLop, 
                 Vector<SinhVien> &dsSV,
                 Vector<PhieuDiemDanh> &dsDD) {
  int choice;
  do {
    printHeader("4. TIM KIEM");
    std::cout << "    1. Tim diem danh theo ngay cua lop\n";
    std::cout << "    2. Tim lich su diem danh theo MSSV\n";
    std::cout << "    3. Xem cac ngay diem danh cua lop\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 3);
    switch (choice) {
    case 1: {
      String maLop, ngay;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        break;
      }
      while (true) {
        Validation::nhapChuoi("  Ngay (DD/MM/YYYY)", ngay);
        if (Validation::isValidDate(ngay))
          break;
        std::cout << "  [!] Ngay khong hop le hoac sai dinh dang. Vui long nhap lai.\n";
      }
      Vector<PhieuDiemDanh> result;
      Search::timDiemDanhTheoNgayVaLop(dsDD, ngay, maLop, result);
      if (result.size() == 0) {
        std::cout << "  [!] Khong co du lieu diem danh ngay " << ngay << " lop " << maLop << ".\n";
        break;
      }
      printDynamicSeparator(61);
      std::cout << "  [I] Ket qua — " << (int)result.size() << " phieu:\n";
      printDynamicSeparator(61);
      std::cout << "  " << std::left << std::setw(4)  << "STT"
                << std::setw(12) << "MSSV"
                << std::setw(30) << "Ho Ten"
                << "Trang thai\n";
      printDynamicSeparator(61);
      for (int i = 0; i < (int)result.size(); ++i) {
        int idx = Search::timSinhVienTheoMSSV(dsSV, result[i].mssv);
        String ten = (idx >= 0) ? dsSV[idx].hoTen : String("?");
        String ttStr = result[i].trangThai == TrangThaiDD::CO_MAT   ? String("Co mat")
                     : result[i].trangThai == TrangThaiDD::VANG_PHEP ? String("Vang co phep")
                                                                  : String("Vang khong phep");
        std::cout << "  " << std::left << std::setw(4)  << (i + 1)
                  << std::setw(12) << result[i].mssv
                  << std::setw(30) << ten
                  << ttStr << "\n";
      }
      printDynamicSeparator(61);
      break;
    }
    case 2: {
      String mssv;
      Validation::nhapChuoi("  MSSV", mssv);
      if (Search::timSinhVienTheoMSSV(dsSV, mssv) == -1) {
        std::cout << "  [!] Sinh vien voi MSSV '" << mssv << "' khong ton tai!\n";
        break;
      }
      Vector<PhieuDiemDanh> result;
      Search::timDiemDanhTheoMSSV(dsDD, mssv, result);
      int idx = Search::timSinhVienTheoMSSV(dsSV, mssv);
      if (idx >= 0)
        std::cout << "\n  Lich su diem danh cua: " << dsSV[idx].hoTen << " (" << mssv << ")\n";
      printDynamicSeparator(48);
      std::cout << "  " << std::left << std::setw(4)  << "STT"
                << std::setw(12) << "Ngay"
                << std::setw(12) << "Lop"
                << std::setw(20) << "Trang thai" << "\n";
      printDynamicSeparator(48);
      for (int i = 0; i < (int)result.size(); ++i) {
        String ttStr = result[i].trangThai == TrangThaiDD::CO_MAT   ? String("Co mat")
                     : result[i].trangThai == TrangThaiDD::VANG_PHEP ? String("Vang co phep")
                                                                  : String("Vang khong phep");
        std::cout << "  " << std::left << std::setw(4)  << (i + 1)
                  << std::setw(12) << result[i].ngay
                  << std::setw(12) << result[i].maLop
                  << std::setw(20) << ttStr << "\n";
      }
      printDynamicSeparator(48);
      if (result.size() == 0)
        std::cout << "  [I] Khong co du lieu.\n";
      break;
    }
    case 3: {
      String maLop;
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        break;
      }
      // Lay toan bo phieu cua lop, sau do loc ngay unique
      Vector<PhieuDiemDanh> allDD;
      Search::timDiemDanhTheoLop(dsDD, maLop, allDD);
      if (allDD.size() == 0) {
        std::cout << "  [I] Lop '" << maLop << "' chua co phieu diem danh nao.\n";
        break;
      }
      Vector<String> ngayDD;
      for (int i = 0; i < (int)allDD.size(); ++i) {
        bool trung = false;
        for (int j = 0; j < (int)ngayDD.size(); ++j) {
          if (ngayDD[j] == allDD[i].ngay) { trung = true; break; }
        }
        if (!trung) ngayDD.push_back(allDD[i].ngay);
      }
      std::cout << "\n  Cac ngay da diem danh cua Lop " << maLop
                << " (" << (int)ngayDD.size() << " buoi):\n";
      printDynamicSeparator(20);
      std::cout << "  " << std::left << std::setw(4) << "STT"
                << std::setw(16) << "Ngay" << "\n";
      printDynamicSeparator(20);
      for (int i = 0; i < (int)ngayDD.size(); ++i) {
        std::cout << "  " << std::left << std::setw(4) << (i + 1)
                  << std::setw(16) << ngayDD[i] << "\n";
      }
      printDynamicSeparator(20);
      break;
    }
    }
  } while (choice != 0);
}

// --- Bao cao & Thong ke ---
void menuBaoCao(Vector<LopHoc> &dsLop, 
                Vector<SinhVien> &dsSV,
                Vector<PhieuDiemDanh> &dsDD, 
                const char* exportDir) {
  int choice;
  do {
    printHeader("6. BAO CAO & THONG KE");
    std::cout << "    1. Thong ke si so theo tung buoi hoc\n";
    std::cout << "    2. Danh sach SV vang nhieu nhat\n";
    std::cout << "    3. Xem ti le vang toan lop\n";
    std::cout << "    4. Xuat bao cao ra file .txt\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 4);
    String maLop;
    if (choice >= 1 && choice <= 4) {
      Validation::nhapChuoi("  Ma lop", maLop);
      if (Search::timLopHocTheoMa(dsLop, maLop) == -1) {
        std::cout << "  [!] Ma lop '" << maLop << "' khong ton tai!\n";
        continue;
      }
    }
    switch (choice) {
    case 1:
      BaoCao::thongKeSiSoTheoBuoi(dsDD, maLop);
      break;
    case 2: {
      int n = Validation::nhapSoNguyen("  Top N sinh vien", 1, 100);
      BaoCao::danhSachVangNhieu(dsSV, dsDD, dsLop, maLop, n);
      break;
    }
    case 3:
      BaoCao::xemTiLeVangToanLop(dsSV, dsDD, dsLop, maLop);
      break;
    case 4:
      BaoCao::xuatBaoCaoFile(dsSV, dsDD, dsLop, maLop, exportDir);
      break;
    }
  } while (choice != 0);
}

// --- Sap xep du lieu ---
static void sapXepLopHoc(Vector<LopHoc> &dsLop, const char* pathLop) {
  int tieuChi = Validation::nhapSoNguyen("  1: Ma lop tang dan, "
                                         "2: Ma lop giam dan. Chon", 1, 2);
  if (tieuChi == 1) {
    Sort::sort(dsLop, [](const LopHoc& a, const LopHoc& b) { return a.maLop < b.maLop; });
  } else {
    Sort::sort(dsLop, [](const LopHoc& a, const LopHoc& b) { return a.maLop > b.maLop; });
  }
  FileIO::saveLopHoc(pathLop, dsLop);
  std::cout << "  [OK] Da sap xep va luu danh sach Lop hoc.\n";
}

static void sapXepSinhVien(Vector<SinhVien> &dsSV, const char* pathSV) {
  int tc = Validation::nhapSoNguyen("  1: Theo MSSV, 2: Theo Ma lop -> Ho ten -> MSSV. Chon", 1, 2);
  int huong = Validation::nhapSoNguyen("  1: Tang dan, 2: Giam dan. Chon", 1, 2);
  if (tc == 1) {
    if (huong == 1) {
      Sort::sort(dsSV, [](const SinhVien& a, const SinhVien& b) { return a.mssv < b.mssv; });
    } else {
      Sort::sort(dsSV, [](const SinhVien& a, const SinhVien& b) { return a.mssv > b.mssv; });
    }
  } else {
    auto cmp = [](const SinhVien& a, const SinhVien& b) {
      if (a.maLop != b.maLop) return a.maLop < b.maLop;
      String hoDemA, tenA, hoDemB, tenB;
      tachTen(a.hoTen, hoDemA, tenA);
      tachTen(b.hoTen, hoDemB, tenB);
      if (tenA != tenB) return tenA < tenB;
      if (hoDemA != hoDemB) return hoDemA < hoDemB;
      return a.mssv < b.mssv;
    };
    auto cmpDesc = [](const SinhVien& a, const SinhVien& b) {
      if (a.maLop != b.maLop) return a.maLop > b.maLop;
      String hoDemA, tenA, hoDemB, tenB;
      tachTen(a.hoTen, hoDemA, tenA);
      tachTen(b.hoTen, hoDemB, tenB);
      if (tenA != tenB) return tenA > tenB;
      if (hoDemA != hoDemB) return hoDemA > hoDemB;
      return a.mssv > b.mssv;
    };
    if (huong == 1) Sort::sort(dsSV, cmp);
    else Sort::sort(dsSV, cmpDesc);
  }
  FileIO::saveSinhVien(pathSV, dsSV);
  std::cout << "  [OK] Da sap xep va luu danh sach Sinh vien.\n";
}

static void sapXepDiemDanh(Vector<PhieuDiemDanh> &dsDD, const char* pathDD) {
  std::cout << "  Sap xep danh sach diem danh theo thu tu Ma lop -> Ngay -> MSSV\n";
  int huong = Validation::nhapSoNguyen("  1: Tang dan, 2: Giam dan. Chon", 1, 2);
  auto cmp = [](const PhieuDiemDanh& a, const PhieuDiemDanh& b) {
    if (a.maLop != b.maLop) return a.maLop < b.maLop;
    long long dateA = parseDate(a.ngay);
    long long dateB = parseDate(b.ngay);
    if (dateA != dateB) return dateA < dateB;
    return a.mssv < b.mssv;
  };
  auto cmpDesc = [](const PhieuDiemDanh& a, const PhieuDiemDanh& b) {
    if (a.maLop != b.maLop) return a.maLop > b.maLop;
    long long dateA = parseDate(a.ngay);
    long long dateB = parseDate(b.ngay);
    if (dateA != dateB) return dateA > dateB;
    return a.mssv > b.mssv;
  };
  if (huong == 1) Sort::sort(dsDD, cmp);
  else Sort::sort(dsDD, cmpDesc);
  FileIO::saveDiemDanh(pathDD, dsDD);
  std::cout << "  [OK] Da sap xep va luu danh sach Diem danh.\n";
}

void menuSapXep(Vector<LopHoc> &dsLop, 
                Vector<SinhVien> &dsSV, 
                Vector<PhieuDiemDanh> &dsDD, 
                const char* pathLop, 
                const char* pathSV, 
                const char* pathDD) {
  int choice;
  do {
    printHeader("5. SAP XEP DU LIEU");
    std::cout << "    1. Sap xep danh sach Lop hoc\n";
    std::cout << "    2. Sap xep danh sach Sinh vien\n";
    std::cout << "    3. Sap xep danh sach Diem danh\n";
    std::cout << "    0. Quay lai menu chinh\n";
    printSeparator();
    choice = Validation::nhapSoNguyen("  Chon", 0, 3);
    switch (choice) {
    case 1:
      sapXepLopHoc(dsLop, pathLop);
      break;
    case 2:
      sapXepSinhVien(dsSV, pathSV);
      break;
    case 3:
      sapXepDiemDanh(dsDD, pathDD);
      break;
    }
  } while (choice != 0);
}

// --- Menu Chinh ---
void hienThiMenuChinh() {
  printHeader("HE THONG QUAN LY DIEM DANH LOP HOC");
  std::cout << "    1. Quan ly Lop hoc\n";
  std::cout << "    2. Quan ly Sinh vien\n";
  std::cout << "    3. Diem danh\n";
  std::cout << "    4. Tim kiem\n";
  std::cout << "    5. Sap xep\n";
  std::cout << "    6. Bao cao & Thong ke\n";
  std::cout << "    0. Thoat chuong trinh\n";
  printSeparator();
}
