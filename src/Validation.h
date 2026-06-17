#pragma once
#include "CustomString.h"
#include "Models.h"

namespace Validation {

bool isValidDate(const String& ngay);
bool isValidMSSV(const String& mssv);
bool isValidTrangThai(char tt);
bool isValidMaLop(const String& maLop);

void nhapChuoi(const char* label, String& dest, int maxLen = 255);
int nhapSoNguyen(const char* label, int minVal, int maxVal);
TrangThaiDD nhapTrangThai(const char* tenSV);

bool nhapXacNhan(const char* label);
bool nhapChuoiCoBaoLuu(const char* label, String& dest, int maxLen = 255);
bool nhapSoNguyenCoBaoLuu(const char* label, int& dest, int minVal, int maxVal);

}  // namespace Validation
