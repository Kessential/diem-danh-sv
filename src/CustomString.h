#pragma once
#include <iostream>

class String {
private:
  char *data;
  size_t len;

public:
  String();
  String(const char *s);
  String(const String &other);
  ~String();

  String &operator=(const String &other);
  String &operator=(const char *s);

  String(String &&other) noexcept;
  String &operator=(String &&other) noexcept;

  size_t length() const;
  const char *c_str() const;
  bool empty() const;

  char operator[](size_t i) const;
  char &operator[](size_t i);

  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;
  bool operator<(const String &other) const;
  bool operator>(const String &other) const;
  bool operator==(const char *s) const;
  bool operator!=(const char *s) const;
  bool operator<(const char *s) const;
  bool operator>(const char *s) const;

  bool equalsIgnoreCase(const String &other) const;
  bool equalsIgnoreCase(const char *s) const;

  String operator+(const String &other) const;
  String &operator+=(const String &other);

  friend std::ostream &operator<<(std::ostream &os, const String &str);
  friend std::istream &operator>>(std::istream &is, String &str);
  friend std::istream &getline(std::istream &is, String &str);
};