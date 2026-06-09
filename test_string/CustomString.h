#pragma once
#include <iostream>

using namespace std; 
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
    char& operator[](int i);

    CustomString operator+(const CustomString& other) const;
    CustomString& operator+=(const CustomString& other);

    // Khai báo friend dạng tự do không dùng std::
    friend bool operator==(const CustomString& lhs, const CustomString& rhs);
    friend bool operator!=(const CustomString& lhs, const CustomString& rhs);
    friend bool operator<(const CustomString& lhs, const CustomString& rhs);
    friend bool operator>(const CustomString& lhs, const CustomString& rhs);

    friend ostream& operator<<(ostream& os, const CustomString& str);
    friend istream& operator>>(istream& is, CustomString& str);
    friend istream& getline(istream& is, CustomString& str);
};