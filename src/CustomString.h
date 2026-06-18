#pragma once
#include <iostream>

class String {
 private:
  char* data;
  size_t len;

 public:
  // --- Constructor & Destructor ---
  String();
  String(const char* s);
  String(const String& other);
  ~String();

  // --- Toan tu gan (Copy & Move) ---
  String& operator=(const String& other);
  String& operator=(const char* s);

  String(String&& other) noexcept;
  String& operator=(String&& other) noexcept;

  // --- Cac ham tien ich ---
  size_t length() const;
  const char* c_str() const;
  bool empty() const;
  int toInt() const;
  String substring(size_t start, size_t count) const;

  // Truy cap ky tu tai vi tri i
  char operator[](size_t i) const;
  char& operator[](size_t i);

  // Cac toan tu so sanh chuoi co phan biet hoa thuong
  bool operator==(const String& other) const;
  bool operator!=(const String& other) const;
  bool operator<(const String& other) const;
  bool operator>(const String& other) const;
  bool operator==(const char* s) const;
  bool operator!=(const char* s) const;
  bool operator<(const char* s) const;
  bool operator>(const char* s) const;

  // So sanh chuoi khong phan biet hoa thuong
  bool equalsIgnoreCase(const String& other) const;
  bool equalsIgnoreCase(const char* s) const;

  // Toan tu noi chuoi
  String operator+(const String& other) const;
  String& operator+=(const String& other);

  // Cac ham ho tro nhap xuat I/O stream
  friend std::ostream& operator<<(std::ostream& os, const String& str);
  friend std::istream& operator>>(std::istream& is, String& str);
  friend std::istream& getline(std::istream& is, String& str);
};