#include "CustomString.h"

// ========================================================
// Ham helper thay the <cstring>
// ========================================================

static size_t my_strlen(const char *s) {
  if (s == nullptr)
    return 0;
  size_t length = 0;
  while (s[length] != '\0') {
    length++;
  }
  return length;
}

static void my_memcpy(char *dest, const char *src, size_t n) {
  if (!dest || !src)
    return;
  for (size_t i = 0; i < n; ++i) {
    dest[i] = src[i];
  }
}

static int my_strcmp(const char *s1, const char *s2) {
  if (s1 == s2)
    return 0;
  if (s1 == nullptr)
    return -1;
  if (s2 == nullptr)
    return 1;

  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return static_cast<unsigned char>(*s1) - static_cast<unsigned char>(*s2);
}

static int my_stricasecmp(const char *s1, const char *s2) {
  if (s1 == s2)
    return 0;
  if (s1 == nullptr)
    return -1;
  if (s2 == nullptr)
    return 1;

  while (*s1 != '\0' && *s2 != '\0') {
    char c1 = *s1;
    char c2 = *s2;
    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
    if (c1 != c2) break;
    s1++;
    s2++;
  }
  char c1 = *s1;
  char c2 = *s2;
  if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
  if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
  return static_cast<unsigned char>(c1) - static_cast<unsigned char>(c2);
}

// ========================================================
// Cai dat class String
// ========================================================

// Default constructor
String::String() : data(nullptr), len(0) {}

String::String(const char *s) {
  if (s == nullptr || s[0] == '\0') {
    data = nullptr;
    len = 0;
  } else {
    len = my_strlen(s);
    data = new char[len + 1];
    my_memcpy(data, s, len + 1);
  }
}

String::String(const String &other) {
  if (other.data == nullptr) {
    data = nullptr;
    len = 0;
  } else {
    len = other.len;
    data = new char[len + 1];
    my_memcpy(data, other.data, len + 1);
  }
}

String::~String() { delete[] data; }

String::String(String &&other) noexcept : data(other.data), len(other.len) {
  other.data = nullptr;
  other.len = 0;
}

String &String::operator=(String &&other) noexcept {
  if (this != &other) {
    delete[] data;
    data = other.data;
    len = other.len;

    other.data = nullptr;
    other.len = 0;
  }
  return *this;
}

// Copy-and-swap idiom
String &String::operator=(const String &other) {
  if (this != &other) {
    String temp(other);

    char *tempData = this->data;
    this->data = temp.data;
    temp.data = tempData;

    size_t tempLen = this->len;
    this->len = temp.len;
    temp.len = tempLen;
  }
  return *this;
}

String &String::operator=(const char *s) {
  if (this->data == s)
    return *this;

  String temp(s);

  char *tempData = this->data;
  this->data = temp.data;
  temp.data = tempData;

  size_t tempLen = this->len;
  this->len = temp.len;
  temp.len = tempLen;

  return *this;
}

size_t String::length() const { return len; }

// Neu data == nullptr thi tra ve chuoi rong tinh cho cout
const char *String::c_str() const { return data ? data : ""; }

bool String::empty() const { return len == 0; }

char String::operator[](size_t i) const { return data[i]; }
char &String::operator[](size_t i) { return data[i]; }

bool String::operator==(const String &other) const {
  return my_strcmp(c_str(), other.c_str()) == 0;
}
bool String::operator!=(const String &other) const {
  return my_strcmp(c_str(), other.c_str()) != 0;
}
bool String::operator<(const String &other) const {
  return my_strcmp(c_str(), other.c_str()) < 0;
}
bool String::operator>(const String &other) const {
  return my_strcmp(c_str(), other.c_str()) > 0;
}

bool String::operator==(const char *s) const {
  return my_strcmp(c_str(), s ? s : "") == 0;
}
bool String::operator!=(const char *s) const {
  return my_strcmp(c_str(), s ? s : "") != 0;
}
bool String::operator<(const char *s) const {
  return my_strcmp(c_str(), s ? s : "") < 0;
}
bool String::operator>(const char *s) const {
  return my_strcmp(c_str(), s ? s : "") > 0;
}

bool String::equalsIgnoreCase(const String &other) const {
  return my_stricasecmp(c_str(), other.c_str()) == 0;
}

bool String::equalsIgnoreCase(const char *s) const {
  return my_stricasecmp(c_str(), s ? s : "") == 0;
}

String String::operator+(const String &other) const {
  if (len == 0 && other.len == 0)
    return String();
  if (len == 0)
    return other;
  if (other.len == 0)
    return *this;

  String result;
  result.len = len + other.len;
  result.data = new char[result.len + 1];

  my_memcpy(result.data, data, len);
  my_memcpy(result.data + len, other.data, other.len + 1);

  return result;
}

String &String::operator+=(const String &other) {
  if (other.len == 0)
    return *this;

  if (this == &other) {
    String temp = *this + other;
    // Dung static_cast<String&&> thay cho std::move
    *this = static_cast<String &&>(temp);
    return *this;
  }

  size_t newLen = len + other.len;
  char *newData = new char[newLen + 1];

  if (len > 0)
    my_memcpy(newData, data, len);
  my_memcpy(newData + len, other.data, other.len + 1);

  delete[] data;
  data = newData;
  len = newLen;

  return *this;
}

std::ostream &operator<<(std::ostream &os, const String &str) {
  os << str.c_str(); // Goi c_str() de dam bao ko in nullptr
  return os;
}

std::istream &operator>>(std::istream &is, String &str) {
  char buffer[4096];

  std::streamsize userWidth = is.width();
  std::streamsize safeWidth = (userWidth > 0 && userWidth < sizeof(buffer))
                                  ? userWidth
                                  : sizeof(buffer);

  is.width(safeWidth);

  if (is >> buffer) {
    str = buffer;
  }

  return is;
}

std::istream &getline(std::istream &is, String &str) {
  size_t capacity = 16;
  char *buf = new char[capacity];
  size_t len = 0;
  buf[0] = '\0';

  char ch;
  while (is.get(ch) && ch != '\n') {
    if (len + 1 >= capacity) {
      capacity *= 2;
      char *newData = new char[capacity];
      my_memcpy(newData, buf, len);
      delete[] buf;
      buf = newData;
    }
    buf[len++] = ch;
  }
  buf[len] = '\0';

  // Tao string temp va gan Move (Thay vi gan thang con tro de rui ro)
  String temp;
  temp.data = buf;
  temp.len = len;

  // Dung static_cast<String&&> thay cho std::move
  str = static_cast<String &&>(temp);

  return is;
}