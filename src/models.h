#pragma once
#include <string>

struct ThoiKhoaBieu {
    int thu;
    int tietBatDau;
    int soTiet;
    std::string phong;
};

struct LopHoc {
    std::string maLop;
    std::string tenLop;
    std::string giangVien;
    ThoiKhoaBieu tkb;
    int tongSoBuoi;
};