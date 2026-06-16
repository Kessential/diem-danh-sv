#include "doctest.h"
#include "../src/Validation.h"
#include <sstream>
#include <iostream>
#include <string>

// Lớp hỗ trợ giả lập luồng nhập/xuất để test các hàm interactive
class StreamRedirector {
    std::streambuf* oldCin;
    std::streambuf* oldCout;
    std::istringstream in;
    std::ostringstream out;
public:
    StreamRedirector(const std::string& input) : in(input) {
        oldCin = std::cin.rdbuf(in.rdbuf());
        oldCout = std::cout.rdbuf(out.rdbuf());
    }
    ~StreamRedirector() {
        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
    }
    std::string getOutput() const { return out.str(); }
};

TEST_CASE("Validation Input - nhapChuoi") {
    SUBCASE("Nhap chuoi hop le") {
        StreamRedirector sr("Hello World\n");
        String dest;
        Validation::nhapChuoi("Nhap", dest);
        CHECK(dest == "Hello World");
    }

    SUBCASE("Nhap chuoi rong truoc, sau do nhap hop le") {
        // \n đầu tiên sẽ bị từ chối vì chuỗi rỗng
        StreamRedirector sr("\nValid String\n");
        String dest;
        Validation::nhapChuoi("Nhap", dest);
        CHECK(dest == "Valid String");
        // Output phải chứa thông báo lỗi "Khong duoc de trong"
        CHECK(sr.getOutput().find("Khong duoc de trong") != std::string::npos);
    }

    SUBCASE("Chuoi vuot qua gioi han buf (gay failbit) hoac maxLen") {
        // Tạo chuỗi rất dài (> 512 ký tự) để test std::cin.getline failbit overflow buffer
        std::string longInput(600, 'A');
        longInput += "\nShort\n"; 
        StreamRedirector sr(longInput);
        String dest;
        // Hàm nhapChuoi có maxLen mặc định là 255. 
        // Lần getline đầu tiên sẽ fail do > 512. Hàm sẽ clear failbit, ignore và yêu cầu nhập lại.
        // Lần thứ 2 nó đọc "Short"
        Validation::nhapChuoi("Nhap", dest);
        CHECK(dest == "Short");
    }
    
    SUBCASE("Chuoi dai vuot maxLen nhung van duoi 512") {
        std::string longInput(300, 'A');
        longInput += "\n";
        StreamRedirector sr(longInput);
        String dest;
        Validation::nhapChuoi("Nhap", dest, 255);
        // Ky vong chuoi bi cat bớt còn 255 ky tu
        CHECK(dest.length() == 255);
    }
}

TEST_CASE("Validation Input - nhapSoNguyen") {
    SUBCASE("Nhap dung so nguyen") {
        StreamRedirector sr("42\n");
        int val = Validation::nhapSoNguyen("Nhap", 1, 100);
        CHECK(val == 42);
    }

    SUBCASE("Nhap vuot range, sau do nhap dung") {
        StreamRedirector sr("0\n101\n50\n");
        int val = Validation::nhapSoNguyen("Nhap", 1, 100);
        CHECK(val == 50);
        CHECK(sr.getOutput().find("Gia tri khong hop le") != std::string::npos);
    }

    SUBCASE("Nhap chu, ky tu dac biet, sau do nhap dung") {
        StreamRedirector sr("abc\n!@#\n-10\n15\n");
        int val = Validation::nhapSoNguyen("Nhap", 1, 100);
        CHECK(val == 15);
    }
}

TEST_CASE("Validation Input - nhapXacNhan") {
    SUBCASE("Chap nhan Y, y, N, n") {
        {
            StreamRedirector sr("y\n");
            CHECK(Validation::nhapXacNhan("Xac nhan") == true);
        }
        {
            StreamRedirector sr("N\n");
            CHECK(Validation::nhapXacNhan("Xac nhan") == false);
        }
        {
            StreamRedirector sr("yes\n"); // Lấy ký tự đầu tiên
            CHECK(Validation::nhapXacNhan("Xac nhan") == true);
        }
    }

    SUBCASE("Nhap sai roi nhap dung") {
        StreamRedirector sr("\n \nO\ny\n");
        CHECK(Validation::nhapXacNhan("Xac nhan") == true);
        CHECK(sr.getOutput().find("Vui long nhap y hoac n") != std::string::npos);
    }
}

TEST_CASE("Validation Input - nhapChuoiCoBaoLuu") {
    SUBCASE("Nguoi dung an Enter ngay lap tuc (De trong)") {
        StreamRedirector sr("\n");
        String dest = "Old Value";
        bool changed = Validation::nhapChuoiCoBaoLuu("Sua", dest);
        CHECK(changed == false);
        CHECK(dest == "Old Value"); // Khong bi thay doi
    }

    SUBCASE("Nguoi dung nhap gia tri moi") {
        StreamRedirector sr("New Value\n");
        String dest = "Old Value";
        bool changed = Validation::nhapChuoiCoBaoLuu("Sua", dest);
        CHECK(changed == true);
        CHECK(dest == "New Value");
    }
}

TEST_CASE("Validation Input - nhapSoNguyenCoBaoLuu") {
    SUBCASE("Nguoi dung an Enter de giu nguyen") {
        StreamRedirector sr("\n");
        int dest = 10;
        bool changed = Validation::nhapSoNguyenCoBaoLuu("Sua", dest, 1, 100);
        CHECK(changed == false);
        CHECK(dest == 10);
    }

    SUBCASE("Nguoi dung nhap chuoi thay vi so") {
        StreamRedirector sr("abc\n20\n"); // Nhap abc se loi, bat nhap lai
        int dest = 10;
        bool changed = Validation::nhapSoNguyenCoBaoLuu("Sua", dest, 1, 100);
        CHECK(changed == true);
        CHECK(dest == 20);
        CHECK(sr.getOutput().find("Gia tri khong hop le") != std::string::npos);
    }

    SUBCASE("Nguoi dung nhap so vuot bien") {
        StreamRedirector sr("200\n50\n");
        int dest = 10;
        bool changed = Validation::nhapSoNguyenCoBaoLuu("Sua", dest, 1, 100);
        CHECK(changed == true);
        CHECK(dest == 50);
    }
}
