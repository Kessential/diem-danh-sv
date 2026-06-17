#include "Vector.h"
#include "Models.h"
#include "FileIO.h"
#include "Menu.h"
#include "Validation.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  Vector<LopHoc>        dsLopHoc;
  Vector<SinhVien>      dsSinhVien;
  Vector<PhieuDiemDanh> dsDiemDanh;

  if (!FileIO::loadLopHoc(PATH_LOPHOC, dsLopHoc)) {
    std::cout << "[INFO] Khong doc duoc '" << PATH_LOPHOC
              << "', bat dau voi danh sach rong.\n";
  }

  if (!FileIO::loadSinhVien(PATH_SINHVIEN, dsSinhVien)) {
    std::cout << "[INFO] Khong doc duoc '" << PATH_SINHVIEN
              << "', bat dau voi danh sach rong.\n";
  }

  if (!FileIO::loadDiemDanh(PATH_DIEMDANH, dsDiemDanh)) {
    std::cout << "[INFO] Khong doc duoc '" << PATH_DIEMDANH
              << "', bat dau voi danh sach rong.\n";
  }

  std::cout << "\n  [OK] Nap du lieu thanh cong:\n";
  std::cout << "       Lop hoc  : " << (int)dsLopHoc.size() << "\n";
  std::cout << "       Sinh vien: " << (int)dsSinhVien.size() << "\n";
  std::cout << "       Diem danh: " << (int)dsDiemDanh.size() << " phieu\n\n";

  int choice;
  do {
    hienThiMenuChinh();
    choice = Validation::nhapSoNguyen("  Chon chuc nang", 0, 5);
    switch (choice) {
    case 1: menuQuanLyLopHoc(dsLopHoc); break;
    case 2: menuQuanLySinhVien(dsSinhVien, dsLopHoc); break;
    case 3: menuDiemDanh(dsLopHoc, dsSinhVien, dsDiemDanh); break;
    case 4: menuTimKiem(dsLopHoc, dsSinhVien, dsDiemDanh); break;
    case 5: menuBaoCao(dsLopHoc, dsSinhVien, dsDiemDanh); break;
    case 0: std::cout << "\n  Tam biet! Hen gap lai.\n\n"; break;
    }
  } while (choice != 0);

  return 0;
}
