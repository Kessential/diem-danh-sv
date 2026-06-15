#pragma once
#include "CustomString.h"

enum class TrangThaiDD : char { 
    CO_MAT = 'C', 
    VANG_PHEP = 'P', 
    VANG_KHONG_PHEP = 'K' 
};

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
    char trangThai;
};

struct ThongKeSinhVien {
    String mssv;
    String hoTen;
    int soVang;
    int soVangKhongPhep;
    float tiLe;
    bool nguyCoiCamThi;
};

struct ThongKeBuoi {
    String ngay;
    int soCoMat;
    int soVangPhep;
    int soVangKhongPhep;
};