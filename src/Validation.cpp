#include "Validation.h"
#include "Models.h"
#include <iostream>
#include <limits>

namespace Validation {

// Helper functions
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

// Kiem tra chuoi ngay hop le (DD/MM/YYYY)
bool isValidDate(const String &ngay) {
  if (ngay.length() != 10) return false;
  if (ngay[2] != '/' || ngay[5] != '/') return false;

  for (size_t i = 0; i < 10; ++i) {
    if (i == 2 || i == 5) continue;
    if (!my_isdigit(ngay[i])) return false;
  }

  char ddBuf[3] = {ngay[0], ngay[1], '\0'};
  char mmBuf[3] = {ngay[3], ngay[4], '\0'};
  char yyBuf[5] = {ngay[6], ngay[7], ngay[8], ngay[9], '\0'};

  int dd = String(ddBuf).toInt();
  int mm = String(mmBuf).toInt();
  int yy = String(yyBuf).toInt();

  if (yy < 2000 || yy > 2100) return false;
  if (mm < 1 || mm > 12) return false;

  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)) {
    daysInMonth[2] = 29;
  }
  if (dd < 1 || dd > daysInMonth[mm]) return false;
  return true;
}

bool isValidMSSV(const String &mssv) {
  if (mssv.empty() || mssv.length() > 20) return false;
  for (size_t i = 0; i < mssv.length(); ++i) {
    if (!my_isalnum(mssv[i])) return false;
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

// Nhap chuoi an toan voi class String tu dinh nghia
void nhapChuoi(const char *label, String &dest, int maxLen) {
  String temp;
  while (true) {
    std::cout << "  " << label << ": ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (temp.empty()) {
      std::cout << "  [!] Khong duoc de trong. Vui long nhap lai.\n";
      continue;
    }
    dest = temp;
    return;
  }
}

int nhapSoNguyen(const char *label, int minVal, int maxVal) {
  int val;
  while (true) {
    std::cout << "  " << label << " (" << minVal << "-" << maxVal << "): ";
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

// Tra ve truc tiep enum thay vi ky tu de an toan kieu (type-safe)
TrangThaiDD nhapTrangThai(const char *tenSV) {
  char tt;
  while (true) {
    std::cout << "  [" << tenSV << "] Trang thai (C=Co mat / P=Vang phep / K=Vang khong phep): ";
    std::cin >> tt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tt = my_toupper(tt);
    if (isValidTrangThai(tt))
      return static_cast<TrangThaiDD>(tt);
    std::cout << "  [!] Chi chap nhan C, P hoac K.\n";
  }
}

bool nhapXacNhan(const char *label) {
  String temp;
  while (true) {
    std::cout << label << " (y/n): ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (!temp.empty()) {
      char c = my_toupper(temp[0]);
      if (c == 'Y') return true;
      if (c == 'N') return false;
    }
    std::cout << "  [!] Vui long nhap y hoac n.\n";
  }
}

bool nhapChuoiCoBaoLuu(const char *label, String &dest, int maxLen) {
  String temp;
  while (true) {
    std::cout << "  " << label << " (hien tai: " << dest.c_str() << ", enter de giu nguyen): ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (temp.empty()) return false;
    dest = temp;
    return true;
  }
}

bool nhapSoNguyenCoBaoLuu(const char *label, int &dest, int minVal, int maxVal) {
  String temp;
  while (true) {
    std::cout << "  " << label << " (hien tai: " << dest << " [" << minVal << "-" << maxVal << "], enter de giu nguyen): ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (temp.empty()) return false;
    
    bool isNumber = true;
    for (size_t i = 0; i < temp.length(); ++i) {
      if (!my_isdigit(temp[i]) && !(i == 0 && temp[0] == '-')) {
        isNumber = false;
        break;
      }
    }
    
    if (isNumber) {
      int val = temp.toInt();
      if (val >= minVal && val <= maxVal) {
        dest = val;
        return true;
      }
    }
    std::cout << "  [!] Gia tri khong hop le. Vui long nhap lai.\n";
  }
}

}
