#include "Validation.h"
#include "Models.h"
#include <iostream>
#include <cstring>
#include <limits>

namespace Validation {

static bool my_isdigit(char c) {
  return c >= '0' && c <= '9';
}

static bool my_isalpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static bool my_isalnum(char c) {
  return my_isdigit(c) || my_isalpha(c);
}

static char my_toupper(char c) {
  if (c >= 'a' && c <= 'z') return c - 32;
  return c;
}

// DD/MM/YYYY
bool isValidDate(const String &ngay) {
  const char *s = ngay.c_str();

  if (ngay.length() != 10)
    return false;
  if (s[2] != '/' || s[5] != '/')
    return false;

  for (int i = 0; i < 10; ++i) {
    if (i == 2 || i == 5)
      continue;
    if (!my_isdigit(s[i]))
      return false;
  }

  int dd = (s[0] - '0') * 10 + (s[1] - '0');
  int mm = (s[3] - '0') * 10 + (s[4] - '0');
  int yy = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 +
           (s[9] - '0');
  if (yy < 2000 || yy > 2100)
    return false;
  if (mm < 1 || mm > 12)
    return false;
  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)) {
    daysInMonth[2] = 29;
  }
  if (dd < 1 || dd > daysInMonth[mm])
    return false;
  return true;
}

bool isValidMSSV(const String &mssv) {
  if (mssv.empty() || mssv.length() > 20)
    return false;
  const char *s = mssv.c_str();
  for (size_t i = 0; i < mssv.length(); ++i) {
    if (!my_isalnum(s[i]))
      return false;
  }
  return true;
}

bool isValidTrangThai(char tt) {
  return tt == static_cast<char>(TrangThaiDD::CO_MAT) ||
         tt == static_cast<char>(TrangThaiDD::VANG_PHEP) ||
         tt == static_cast<char>(TrangThaiDD::VANG_KHONG_PHEP);
}

bool isValidMaLop(const String &maLop) {
  return !maLop.empty() && maLop.length() <= 50;
}

void nhapChuoi(const char *label, String &dest, int maxLen) {
  char buf[512];
  while (true) {
    std::cout << label << ": ";
    std::cin.getline(buf, sizeof(buf));
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int len = strlen(buf);
    if (len == 0) {
      std::cout << "  [!] Khong duoc de trong. Vui long nhap lai.\n";
      continue;
    }

    if (len > maxLen) {
      buf[maxLen] = '\0';
    }
    dest = String(buf);
    return;
  }
}

int nhapSoNguyen(const char *label, int minVal, int maxVal) {
  int val;
  while (true) {
    std::cout << label << " (" << minVal << "-" << maxVal << "): ";
    if (std::cin >> val) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (val >= minVal && val <= maxVal)
        return val;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "  [!] Gia tri khong hop le. Vui long nhap lai.\n";
  }
}

char nhapTrangThai(const char *tenSV) {
  char tt;
  while (true) {
    std::cout << "  [" << tenSV
              << "] Trang thai (C=Co mat / P=Vang phep / K=Vang khong phep): ";
    std::cin >> tt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tt = my_toupper(tt);
    if (isValidTrangThai(tt))
      return tt;
    std::cout << "  [!] Chi chap nhan C, P hoac K.\n";
  }
}

}
