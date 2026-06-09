#include "CustomString.h"
#include <string.h> 
#include <istream>
#include <ostream>

using namespace std;

// 1. Hàm khởi tạo mặc định
CustomString::CustomString() {
    data = new char[1]();
    len = 0;
}

// 2. Hàm khởi tạo từ chuỗi hằng char*
CustomString::CustomString(const char* s) {
    if (s == nullptr) s = "";
    len = strlen(s); // Dùng trực tiếp hàm của <string.h>
    data = new char[len + 1];
    strcpy(data, s);
}

// 3. Hàm khởi tạo sao chép (Copy Constructor)
CustomString::CustomString(const CustomString& other) {
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
}

// 4. Hàm hủy (Destructor)
CustomString::~CustomString() {
    delete[] data;
}

// 5. Toán tử gán đối tượng (=)
CustomString& CustomString::operator=(const CustomString& other) {
    if (this == &other) return *this;
    delete[] data;
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
    return *this;
}

// 6. Toán tử gán chuỗi hằng (=)
CustomString& CustomString::operator=(const char* s) {
    if (s == nullptr) s = "";
    delete[] data;
    len = strlen(s);
    data = new char[len + 1];
    strcpy(data, s);
    return *this;
}

// 7. Các hàm tiện ích bổ trợ
int CustomString::length() const { return len; }
const char* CustomString::c_str() const { return data; }
bool CustomString::empty() const { return len == 0; }

// 8. Toán tử truy cập chỉ số mảng []
char CustomString::operator[](int i) const { return data[i]; }
char& CustomString::operator[](int i) { return data[i]; }

// 9. Các toán tử so sánh độc lập
bool operator==(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) != 0;
}

bool operator<(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>(const CustomString& lhs, const CustomString& rhs) {
    return strcmp(lhs.data, rhs.data) > 0;
}

// 10. Toán tử cộng và nối chuỗi
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

// 11. Toán tử xuất dòng lệnh (cout <<)
ostream& operator<<(ostream& os, const CustomString& str) {
    os << str.data;
    return os;
}

// 12. Toán tử nhập dòng lệnh (cin >>) - Đã sửa lỗi C++20 bằng mảng tạm
istream& operator>>(istream& is, CustomString& str) {
    char temp[4096]; 
    if (is >> temp) {
        delete[] str.data;
        str.len = strlen(temp);
        str.data = new char[str.len + 1];
        strcpy(str.data, temp);
    }
    return is;
}

// 13. Hàm getline tự viết
istream& getline(istream& is, CustomString& str) {
    delete[] str.data;

    int capacity = 16;
    str.data = new char[capacity];
    str.len = 0;
    str.data[0] = '\0';

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