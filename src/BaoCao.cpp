#include "BaoCao.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace BaoCao {

void xayDungThongKe(Vector<SinhVien>& dsSV, 
                    Vector<PhieuDiemDanh>& dsDD,
                    Vector<LopHoc>& dsLop, 
                    const String& maLop,
                    Vector<ThongKeSinhVien>& result) {
  result.clear();
  int tongSoBuoi = 0;
  for (int i = 0; i < (int)dsLop.size(); ++i) {
    if (dsLop[i].maLop == maLop) {
      tongSoBuoi = dsLop[i].tongSoBuoi;
      break;
    }
  }
  for (int i = 0; i < (int)dsSV.size(); ++i) {
    if (dsSV[i].maLop == maLop) {
      ThongKeSinhVien tk =
          DiemDanhManager::tinhTiLeVang(dsDD, dsSV[i], tongSoBuoi);
      result.push_back(tk);
    }
  }
}

static Vector<String> layDanhSachNgayDiemDanh(Vector<PhieuDiemDanh>& dsDD,
                                              const String& maLop) {
  Vector<String> ngayDD;
  for (int i = 0; i < (int)dsDD.size(); ++i) {
    if (dsDD[i].maLop != maLop) continue;
    bool trung = false;
    for (int j = 0; j < (int)ngayDD.size(); ++j) {
      if (ngayDD[j] == dsDD[i].ngay) {
        trung = true;
        break;
      }
    }
    if (!trung) ngayDD.push_back(dsDD[i].ngay);
  }
  return ngayDD;
}

void thongKeSiSoTheoBuoi(Vector<PhieuDiemDanh>& dsDD, const String& maLop) {
  Vector<String> ngayDD = layDanhSachNgayDiemDanh(dsDD, maLop);

  std::cout << "\n  === THONG KE SI SO THEO BUOI — Lop " << maLop << " ===\n\n";
  std::cout << "  " << std::left << std::setw(12) << "Ngay" 
            << std::right << std::setw(9) << "Co mat" 
            << std::setw(11) << "Vang phep"
            << std::setw(12) << "Vang K.phep" 
            << std::setw(12) << "Tong vang\n";
  std::cout
      << "  --------------------------------------------------------------\n";

  for (int i = 0; i < (int)ngayDD.size(); ++i) {
    int coMat = 0, vangP = 0, vangK = 0;
    for (int j = 0; j < (int)dsDD.size(); ++j) {
      if (dsDD[j].maLop != maLop || dsDD[j].ngay != ngayDD[i])
        continue;
      if (dsDD[j].trangThai == TrangThaiDD::CO_MAT)
        ++coMat;
      else if (dsDD[j].trangThai == TrangThaiDD::VANG_PHEP)
        ++vangP;
      else if (dsDD[j].trangThai == TrangThaiDD::VANG_KHONG_PHEP)
        ++vangK;
    }
    std::cout << "  " << std::left << std::setw(12) << ngayDD[i]
              << std::right << std::setw(9) << coMat 
              << std::setw(11) << vangP
              << std::setw(12) << vangK 
              << std::setw(12) << (vangP + vangK) << "\n";
  }
  if (ngayDD.size() == 0) {
    std::cout << "  Chua co du lieu diem danh nao.\n";
  }
}

void danhSachVangNhieu(Vector<SinhVien>& dsSV, 
                       Vector<PhieuDiemDanh>& dsDD,
                       Vector<LopHoc>& dsLop, 
                       const String& maLop, 
                       int topN) {
  Vector<ThongKeSinhVien> dsThongKe;
  xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);

  Sort::sort(dsThongKe, SoVangDesc{});

  int in = (topN > (int)dsThongKe.size()) ? (int)dsThongKe.size() : topN;

  std::cout << "\n  === TOP " << in << " SINH VIEN VANG NHIEU NHAT — Lop "
            << maLop << " ===\n\n";
  std::cout << "  " << std::left << std::setw(4) << "STT" 
            << std::setw(12) << "MSSV" 
            << std::setw(25) << "Ho Ten" 
            << std::right << std::setw(8) << "SoVang" 
            << std::setw(8) << "TiLe%" 
            << std::setw(10) << "CamThi?\n";
  std::cout << "  "
               "---------------------------------------------------------------"
               "----\n";

  for (int i = 0; i < in; ++i) {
    std::cout << "  " << std::left << std::setw(4) << (i + 1) 
              << std::setw(12) << dsThongKe[i].mssv 
              << std::setw(25) << dsThongKe[i].hoTen
              << std::right << std::setw(8) << dsThongKe[i].soVang 
              << std::fixed << std::setprecision(1) << std::setw(7) << dsThongKe[i].tiLe << "%" 
              << std::setw(10) << (dsThongKe[i].nguyCoCamThi ? "[CANH BAO]" : "OK") << "\n";
  }
}

void xemTiLeVangToanLop(Vector<SinhVien>& dsSV, 
                        Vector<PhieuDiemDanh>& dsDD,
                        Vector<LopHoc>& dsLop, 
                        const String& maLop) {
  Vector<ThongKeSinhVien> dsThongKe;
  xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);

  std::cout << "\n  === TI LE VANG TOAN LOP — Lop " << maLop << " ===\n\n";
  std::cout << "  " << std::left << std::setw(12) << "MSSV" 
            << std::setw(25) << "Ho Ten" 
            << std::right << std::setw(8) << "SoVang"
            << std::setw(12) << "VangK.phep" 
            << std::setw(8) << "TiLe%"
            << std::setw(10) << "CamThi?\n";
  std::cout << "  "
               "---------------------------------------------------------------"
               "-------\n";

  for (int i = 0; i < (int)dsThongKe.size(); ++i) {
    std::cout << "  " << std::left << std::setw(12) << dsThongKe[i].mssv
              << std::setw(25) << dsThongKe[i].hoTen 
              << std::right << std::setw(8) << dsThongKe[i].soVang 
              << std::setw(12) << dsThongKe[i].soVangKhongPhep 
              << std::fixed << std::setprecision(1) << std::setw(7) << dsThongKe[i].tiLe << "%"
              << std::setw(10) << (dsThongKe[i].nguyCoCamThi ? "[CANH BAO]" : "OK") << "\n";
  }
}

void xuatBaoCaoFile(Vector<SinhVien>& dsSV, 
                    Vector<PhieuDiemDanh>& dsDD,
                    Vector<LopHoc>& dsLop, 
                    const String& maLop) {
  String tenFile = String("data/baocao_") + maLop + String(".txt");

  std::ofstream out(tenFile.c_str());
  if (!out) {
    std::cout << "  [!] Khong the tao file bao cao: " << tenFile << "\n";
    return;
  }

  out << "BAO CAO DIEM DANH — LOP " << maLop << "\n";
  out << "=========================================\n\n";

  for (int i = 0; i < (int)dsLop.size(); ++i) {
    if (dsLop[i].maLop == maLop) {
      out << "Mon hoc   : " << dsLop[i].tenLop << "\n";
      out << "Giang vien: " << dsLop[i].giangVien << "\n";
      out << "Phong     : " << dsLop[i].tkb.phong 
          << "  |  Thu "    << dsLop[i].tkb.thu 
          << "  |  Tiet "   << dsLop[i].tkb.tietBatDau
          << " - " << (dsLop[i].tkb.tietBatDau + dsLop[i].tkb.soTiet - 1) << "\n";
      out << "Tong so buoi: " << dsLop[i].tongSoBuoi << "\n\n";
      break;
    }
  }

  out << "--- THONG KE SI SO THEO BUOI ---\n";
  // Day truc tiep vao out de tranh tran bo nho buffer
  out << std::left << std::setw(12) << "Ngay" 
      << std::right << std::setw(9) << "Co mat" 
      << std::setw(11) << "Vang phep" 
      << std::setw(12) << "Vang K.phep" 
      << std::setw(12) << "Tong vang\n";
  out << "--------------------------------------------------------------\n";

  Vector<String> ngayDD = layDanhSachNgayDiemDanh(dsDD, maLop);
  for (int i = 0; i < (int)ngayDD.size(); ++i) {
    int coMat = 0, vangP = 0, vangK = 0;
    for (int j = 0; j < (int)dsDD.size(); ++j) {
      if (dsDD[j].maLop != maLop || dsDD[j].ngay != ngayDD[i])
        continue;
      if (dsDD[j].trangThai == TrangThaiDD::CO_MAT)
        ++coMat;
      else if (dsDD[j].trangThai == TrangThaiDD::VANG_PHEP)
        ++vangP;
      else if (dsDD[j].trangThai == TrangThaiDD::VANG_KHONG_PHEP)
        ++vangK;
    }
    out << std::left << std::setw(12) << ngayDD[i] 
        << std::right << std::setw(9) << coMat 
        << std::setw(11) << vangP 
        << std::setw(12) << vangK 
        << std::setw(12) << (vangP + vangK) << "\n";
  }

  out << "\n--- TI LE VANG TUNG SINH VIEN ---\n";
  out << std::left << std::setw(12) << "MSSV" 
      << std::setw(25) << "Ho Ten"
      << std::right << std::setw(8) << "SoVang" 
      << std::setw(8) << "TiLe%"
      << std::setw(10) << "CamThi?\n";
  out << "------------------------------------------------------------\n";

  Vector<ThongKeSinhVien> dsThongKe;
  xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);
  Sort::sort(dsThongKe, SoVangDesc{});

  for (int i = 0; i < (int)dsThongKe.size(); ++i) {
    out << std::left << std::setw(12) << dsThongKe[i].mssv 
        << std::setw(25) << dsThongKe[i].hoTen 
        << std::right << std::setw(8) << dsThongKe[i].soVang 
        << std::fixed << std::setprecision(1) << std::setw(7) << dsThongKe[i].tiLe << "%" 
        << std::setw(10) << (dsThongKe[i].nguyCoCamThi ? "[CANH BAO]" : "OK") << "\n";
  }

  out.close();
  std::cout << "  [OK] Bao cao da xuat ra: " << tenFile << "\n";
}

}  // namespace BaoCao
