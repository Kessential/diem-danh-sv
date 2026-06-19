#include "Validation.h"
#include "Models.h"
#include <iostream>
#include <limits>

namespace Validation {

// --- Ham ho tro (internal) ---

// Kiem tra chuoi chi chua space/tab (blank)
static bool isBlankString(const String& s) {
  if (s.empty()) return true;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r') return false;
  }
  return true;
}

// Kiem tra ky tu so
static bool my_isdigit(char c) {
  return c >= '0' && c <= '9';
}

// Kiem tra ky tu chu cai
static bool my_isalpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Kiem tra ky tu chu hoac so
static bool my_isalnum(char c) {
  return my_isdigit(c) || my_isalpha(c);
}

// Chuyen thanh chu in hoa
static char my_toupper(char c) {
  if (c >= 'a' && c <= 'z') return c - 32;
  return c;
}

// --- Ham kiem tra (Validation) ---

// Kiem tra chuoi ngay hop le (DD/MM/YYYY)
bool isValidDate(const String& ngay) {
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

// Kiem tra MSSV chi chua chu/so, toi da 20 ky tu
bool isValidMSSV(const String& mssv) {
  if (mssv.empty() || mssv.length() > 20) return false;
  for (size_t i = 0; i < mssv.length(); ++i) {
    if (!my_isalnum(mssv[i])) return false;
  }
  return true;
}

// Kiem tra trang thai C, P, hoac K
bool isValidTrangThai(char tt) {
  return tt == static_cast<char>(TrangThaiDD::CO_MAT) ||
         tt == static_cast<char>(TrangThaiDD::VANG_PHEP) ||
         tt == static_cast<char>(TrangThaiDD::VANG_KHONG_PHEP);
}

// Kiem tra ma lop khong rong/blank, toi da 50 ky tu
bool isValidMaLop(const String& maLop) {
  return !isBlankString(maLop) && maLop.length() <= 50;
}

// --- Ham nhap lieu (Input) ---

// Nhap chuoi an toan, khong cho phep bo trong
void nhapChuoi(const char* label, String& dest) {
  String temp;
  while (true) {
    std::cout << "  " << label << ": ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (isBlankString(temp)) {
      std::cout << "  [!] Khong duoc de trong. Vui long nhap lai.\n";
      continue;
    }
    dest = temp;
    return;
  }
}

// Nhap so nguyen nam trong khoang minVal - maxVal
int nhapSoNguyen(const char* label, int minVal, int maxVal) {
  int val;
  while (true) {
    std::cout << "  " << label << " (" << minVal << "-" << maxVal << "): ";
    if (std::cin >> val) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (val >= minVal && val <= maxVal) return val;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "  [!] Gia tri khong hop le. Vui long nhap lai.\n";
  }
}

// Nhap trang thai diem danh (C/P/K) va tra ve enum
TrangThaiDD nhapTrangThai(const char* tenSV) {
  char tt;
  while (true) {
    std::cout << "  [" << tenSV
              << "] Trang thai (C=Co mat / P=Vang phep / K=Vang khong phep): ";
    std::cin >> tt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tt = my_toupper(tt);
    if (isValidTrangThai(tt)) return static_cast<TrangThaiDD>(tt);
    std::cout << "  [!] Chi chap nhan C, P hoac K.\n";
  }
}

// Nhap xac nhan y hoac n, tra ve true/false
bool nhapXacNhan(const char* label) {
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

// Nhap chuoi, neu de trong (Enter) thi tra ve false (giu nguyen)
bool nhapChuoiCoBaoLuu(const char* label, String& dest) {
  String temp;
  while (true) {
    std::cout << "  " << label << " (hien tai: " << dest
              << ", enter de giu nguyen): ";
    getline(std::cin, temp);
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (temp.empty()) return false;          // Enter thuan -> giu nguyen
    if (isBlankString(temp)) {               // Toan space -> nhap lai
      std::cout << "  [!] Khong duoc de trong. Vui long nhap lai.\n";
      continue;
    }
    dest = temp;
    return true;
  }
}

// Nhap so nguyen, neu de trong (Enter) thi tra ve false (giu nguyen)
bool nhapSoNguyenCoBaoLuu(const char* label, 
                          int& dest, 
                          int minVal,
                          int maxVal) {
  String temp;
  while (true) {
    std::cout << "  " << label << " (hien tai: " << dest << " [" << minVal
              << "-" << maxVal << "], enter de giu nguyen): ";
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

}  // namespace Validation
