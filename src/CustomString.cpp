#include "CustomString.h"
#include <cstring>
#include <istream>
#include <ostream>

CustomString::CustomString() {
    data = new char[1]();
    len = 0;
}

CustomString::CustomString(const char* s) {
    if (s == nullptr) s = "";
    len = strlen(s);
    data = new char[len + 1];
    strcpy(data, s);
}

CustomString::CustomString(const CustomString& other) {
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
}

CustomString::~CustomString() {
    delete[] data;
}

CustomString& CustomString::operator=(const CustomString& other) {
    if (this == &other) return *this;
    delete[] data;
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
    return *this;
}

CustomString& CustomString::operator=(const char* s) {
    if (s == nullptr) s = "";
    delete[] data;
    len = strlen(s);
    strcpy(data, s);
    return *this;
}

int CustomString::length() const { return len; }
const char* CustomString::c_str() const { return data; }
bool CustomString::empty() const { return len == 0; }

char CustomString::operator[](int i) const { return data[i]; }
char& CustomString::operator[](int i) { return data[i]; }

bool CustomString::operator==(const CustomString& other) const {
    return strcmp(data, other.data) == 0;
}

bool CustomString::operator!=(const CustomString& other) const {
    return strcmp(data, other.data) != 0;
}

bool CustomString::operator<(const CustomString& other) const {
    return strcmp(data, other.data) < 0;
}

bool CustomString::operator>(const CustomString& other) const {
    return strcmp(data, other.data) > 0;
}

bool CustomString::operator==(const char* s) const {
    return strcmp(data, s) == 0;
}

bool CustomString::operator<(const char* s) const {
    return strcmp(data, s) < 0;
}

bool CustomString::operator>(const char* s) const {
    return strcmp(data, s) > 0;
}

bool operator==(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) == 0;
}

bool operator<(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) < 0;
}

CustomString CustomString::operator+(const CustomString& other) const {
    int newLen = len + other.len;
    char* newBuf = new char[newLen + 1];
    strcpy(newBuf, data);
    strcpy(newBuf + len, other.data);
    CustomString result(newBuf);
    delete[] newBuf;
    return result;
}

CustomString& CustomString::operator+=(const CustomString& other) {
    *this = *this + other;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CustomString& str) {
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, CustomString& str) {
    is >> str.data;
    return is;
}

std::istream& getline(std::istream& is, CustomString& str) {
    delete[] str.data;

    int capacity = 16;
    str.data = new char[capacity];
    str.len = 0;
    str.data[0] = 0;

    char ch;

    while (is.get(ch) && ch != '\n') {
        if (str.len + 1 >= capacity) {
            capacity *= 2;
            char* newData = new char[capacity];

            for (int i = 0; i < str.len; ++i) {
                newData[i] = str.data[i];
            }

            delete[] str.data;
            str.data = newData;
        }

        str.data[str.len] = ch;
        ++str.len;
        str.data[str.len] = '\0';
    }
    return is;
}