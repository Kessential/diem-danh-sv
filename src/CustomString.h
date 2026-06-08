#pragma once
#include <iostream>

class CustomString {
private:
  char *data;
  int len;

public:
  CustomString();
  CustomString(const char *s);
  CustomString(const CustomString &other);
  ~CustomString();

  CustomString &operator=(const CustomString &other);
  CustomString &operator=(const char *s);

  int length() const;
  const char *c_str() const;
  bool empty() const;

  char operator[](int i) const;
  char &operator[](int i);

  bool operator==(const CustomString &other) const;
  bool operator!=(const CustomString &other) const;
  bool operator<(const CustomString &other) const;
  bool operator>(const CustomString &other) const;
  bool operator==(const char *s) const;
  bool operator<(const char *s) const;
  bool operator>(const char *s) const;

  friend bool operator==(const CustomString& lhs, const CustomString& rhs);
  friend bool operator<(const CustomString& lhs, const CustomString& rhs);

  CustomString operator+(const CustomString& other) const;
  CustomString& operator+=(const CustomString& other);

  friend std::ostream& operator<<(std::ostream& os, const CustomString& str);
  friend std::istream& operator>>(std::istream& is, CustomString& str);
  friend std::istream& getline(std::istream& is, CustomString& str);
};