#include <iostream>
#include "CustomString.h"

using namespace std;

void inKetQua(bool ketQua) {
    if (ketQua) cout << "--> DUNG (True)\n";
    else cout << "--> SAI (False)\n";
}

// ========================================================
// BÀI TEST 1: KIỂM THỬ KHỞI TẠO CHUỖI VÀ GÁN
// ========================================================
void testKhoiTaoVaGan() {
    cout << "--- [TEST 1] KHOI TAO VA GAN CHUOI ---\n";
    CustomString s1;
    CustomString s2("Nguyen Van A");
    cout << "s1 (khoi tao mac dinh): '" << s1 << "' (Do dai: " << s1.length() << ")\n";
    cout << "s2 (khoi tao co tham so): '" << s2 << "' (Do dai: " << s2.length() << ")\n";

    s1 = "Dan Toan-Tin Bach Khoa"; 
    cout << "s1 sau khi gan chuoi moi: \"" << s1 << "\"\n\n";
}

// ========================================================
// BÀI TEST 2: KIỂM THỬ NỐI CHUỖI (+, +=)
// ========================================================
void testNoiChuoi() {
    cout << "--- [TEST 2] NOI CHUOI TIEU CHUAN ---\n";
    CustomString hoTen("Nguyen Van A");
    CustomString lop("Toan Tin 01");
    
    // Test toán tử +
    CustomString thongTin = hoTen + " - Lop: " + lop;
    cout << "Ket qua toan tu (+): " << thongTin << "\n";

    // Test toán tử +=
    CustomString s("HUST");
    s += " 2026";
    cout << "Ket qua toan tu (+=): " << s << "\n\n";
}

// ========================================================
// BÀI TEST 3: KIỂM THỬ TOÁN TỬ SO SÁNH (==, !=, <, >)
// ========================================================
void testSoSanh() {
    cout << "--- [TEST 3] SO SANH THEO TU DIEN ---\n";
    CustomString strA("abc");
    CustomString strB("def");
    CustomString strC("abc");

    cout << "So sanh (\"abc\" == \"abc\"): ";
    inKetQua(strA == strC);

    cout << "So sanh (\"abc\" == \"def\"): ";
    inKetQua(strA == strB);

    cout << "So sanh (\"abc\" < \"def\"): ";
    inKetQua(strA < strB);
    
    cout << "So sanh (\"def\" > \"abc\"): ";
    inKetQua(strB > strA);
    cout << "\n";
}

// ========================================================
// BÀI TEST 4: KIỂM THỬ NHẬP LIỆU (cin >>, getline)
// ========================================================
void testNhapLieu() {
    cout << "--- [TEST 4] NHAP CHUOI TU BAN PHIM ---\n";
    CustomString tu;
    cout << "1. Nhap mot tu (cin >>, khong co dau cach): ";
    cin >> tu;
    cout << "-> Tu vua nhap: " << tu << " (Do dai: " << tu.length() << ")\n";

    cin.ignore(1000, '\n'); // Xóa bộ đệm dòng trống

    CustomString dong;
    cout << "2. Nhap ca dong (getline, co dau cach thoai mai): ";
    getline(cin, dong);
    cout << "-> Dong vua nhap: " << dong << " (Do dai: " << dong.length() << ")\n\n";
}

// ========================================================
// HÀM MAIN CHÍNH: QUẢN LÝ CÁC BÀI TEST
// ========================================================
int main() {
    cout << "====================================================\n";
    cout << "   HE THONG KIEM THU TOAN DIEN CUSTOM STRING\n";
    cout << "====================================================\n\n";

    testKhoiTaoVaGan(); // Chạy Test 1
    testNoiChuoi();     // Chạy Test 2
    testSoSanh();       // Chạy Test 3
    testNhapLieu();     // Chạy Test 4

    cout << "====================================================\n";
    return 0;
}