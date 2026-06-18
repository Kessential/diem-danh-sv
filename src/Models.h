#pragma once
#include "CustomString.h"

// --- Enum trang thai ---
enum class TrangThaiDD : char {
  CO_MAT = 'C',
  VANG_PHEP = 'P',
  VANG_KHONG_PHEP = 'K'
};

// --- Cac cau truc du lieu co ban ---
struct ThoiKhoaBieu {
  int thu;
  int tietBatDau;
  int soTiet;
  String phong;
};

struct LopHoc {
  String maLop;
  String tenLop;
  String giangVien;
  ThoiKhoaBieu tkb;
  int tongSoBuoi;
};

struct SinhVien {
  String mssv;
  String hoTen;
  String maLop;
};

struct PhieuDiemDanh {
  String mssv;
  String maLop;
  String ngay;
  TrangThaiDD trangThai;
};

// --- Cac cau truc du lieu phuc vu thong ke/bao cao ---
struct ThongKeSinhVien {
  String mssv;
  String hoTen;
  int soVang;
  int soVangKhongPhep;
  float tiLe;
  bool nguyCoCamThi;
};

struct ThongKeBuoi {
  String ngay;
  int soCoMat;
  int soVangPhep;
  int soVangKhongPhep;
};