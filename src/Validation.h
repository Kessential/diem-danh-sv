#pragma once
#include "CustomString.h"

namespace Validation {

bool isValidDate(const String& ngay);
bool isValidMSSV(const String& mssv);
bool isValidTrangThai(char tt);
bool isValidMaLop(const String& maLop);

void nhapChuoi(const char* label, String& dest, int maxLen = 255);
int  nhapSoNguyen(const char* label, int minVal, int maxVal);
char nhapTrangThai(const char* tenSV);

}
