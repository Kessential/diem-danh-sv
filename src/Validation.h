#pragma once
#include "CustomString.h"
#include "Models.h"

namespace Validation {

// Kiem tra dinh dang ngay DD/MM/YYYY
bool isValidDate(const String& ngay);

// Kiem tra MSSV (chi chua chu va so, <= 20 ky tu)
bool isValidMSSV(const String& mssv);

// Kiem tra trang thai (C, P, K)
bool isValidTrangThai(char tt);

// Kiem tra ma lop (khong rong, <= 50 ky tu)
bool isValidMaLop(const String& maLop);

// Nhap chuoi an toan tu ban phim
void nhapChuoi(const char* label, String& dest, int maxLen = 255);

// Nhap so nguyen trong khoang [minVal, maxVal]
int nhapSoNguyen(const char* label, int minVal, int maxVal);

// Nhap trang thai diem danh (C, P, K)
TrangThaiDD nhapTrangThai(const char* tenSV);

// Hoi xac nhan y/n
bool nhapXacNhan(const char* label);

// Nhap chuoi, nhan Enter de giu gia tri cu
bool nhapChuoiCoBaoLuu(const char* label, String& dest, int maxLen = 255);

// Nhap so nguyen, nhan Enter de giu gia tri cu
bool nhapSoNguyenCoBaoLuu(const char* label, int& dest, int minVal, int maxVal);

}  // namespace Validation
