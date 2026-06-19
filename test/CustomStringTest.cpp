#include "doctest.h"
#include "../src/CustomString.h"
#include <string>

TEST_CASE("CustomString - Khởi tạo và cơ bản") {
    SUBCASE("Khởi tạo rỗng") {
        String s;
        CHECK(s.empty() == true);
        CHECK(s.length() == 0);
        CHECK(s.c_str()[0] == '\0'); // Đảm bảo null-terminated
    }

    SUBCASE("Khởi tạo từ char*") {
        String s("Hello");
        CHECK(s.empty() == false);
        CHECK(s.length() == 5);
        CHECK(std::string(s.c_str()) == "Hello");
    }

    SUBCASE("Khởi tạo từ nullptr") {
        String s(nullptr);
        CHECK(s.empty() == true);
        CHECK(s.length() == 0);
    }
}

TEST_CASE("CustomString - Copy và Move Semantics") {
    SUBCASE("Copy constructor") {
        String s1("Test");
        String s2(s1);
        CHECK(s1 == s2);
        CHECK(s1.c_str() != s2.c_str()); // Đảm bảo deep copy
    }

    SUBCASE("Copy assignment") {
        String s1("Test 1");
        String s2("Test 2");
        s2 = s1;
        CHECK(s1 == s2);
        CHECK(s2 == "Test 1");
        CHECK(s1.c_str() != s2.c_str());
    }

    SUBCASE("Tự gán (Self-assignment)") {
        String s("Self");
        s = s;
        CHECK(s == "Self");
        CHECK(s.length() == 4);
    }

    SUBCASE("Move constructor") {
        String s1("Move");
        String s2(std::move(s1));
        CHECK(s2 == "Move");
        CHECK(s1.empty() == true); // s1 bị moved
    }

    SUBCASE("Move assignment") {
        String s1("Move Assign");
        String s2("Old");
        s2 = std::move(s1);
        CHECK(s2 == "Move Assign");
        CHECK(s1.empty() == true);
    }

    SUBCASE("Move assignment tự gán") {
        String s("Move Self");
        String& s_ref = s;
        s = std::move(s_ref);
        CHECK(s == "Move Self");
    }
}

TEST_CASE("CustomString - Các thao tác so sánh và lấy ký tự") {
    SUBCASE("Truy cập ký tự (Index)") {
        String s("abc");
        CHECK(s[0] == 'a');
        CHECK(s[2] == 'c');
        s[1] = 'x';
        CHECK(s == "axc");

        // Out of bounds return '\0' (Giả sử implementation CustomString làm vậy, nếu crash thì sửa lại test)
        // Nếu implementation throw thì dùng CHECK_THROWS. Ở đây C++ thường ko bound check hoặc trả về reference rác
        // Tuy nhiên theo implementation, thường trả về data[i]. Nếu index lớn hơn length, hành vi là UB. Ta test cận dưới.
    }

    SUBCASE("So sánh bằng") {
        String s1("abc");
        String s2("abc");
        String s3("Abc");
        CHECK(s1 == s2);
        CHECK(s1 != s3);
        CHECK(s1 == "abc");
        CHECK(s1 != "Abc");
    }

    SUBCASE("So sánh lớn nhỏ") {
        String s1("abc");
        String s2("abd");
        CHECK(s1 < s2);
        CHECK(s2 > s1);
        CHECK(s1 < "abd");
    }

    SUBCASE("So sánh không phân biệt hoa thường") {
        String s1("HeLlo");
        String s2("hElLO");
        String s3("world");
        CHECK(s1.equalsIgnoreCase(s2));
        CHECK(!s1.equalsIgnoreCase(s3));
        CHECK(s1.equalsIgnoreCase("hello"));
    }
}

TEST_CASE("CustomString - Nối chuỗi") {
    SUBCASE("Toán tử +") {
        String s1("Hello");
        String s2(" World");
        String s3 = s1 + s2;
        CHECK(s3 == "Hello World");
        CHECK(s1 == "Hello"); // s1 không đổi
    }

    SUBCASE("Toán tử + với chuỗi rỗng") {
        String s1("Test");
        String s2("");
        CHECK((s1 + s2) == "Test");
        CHECK((s2 + s1) == "Test");
    }

    SUBCASE("Toán tử +=") {
        String s("A");
        s += "B";
        CHECK(s == "AB");
        s += String("C");
        CHECK(s == "ABC");
    }
    
    SUBCASE("Toán tử += với chuỗi rỗng") {
        String s("A");
        s += "";
        CHECK(s == "A");
    }
}

TEST_CASE("CustomString - Các tiện ích khác") {
    SUBCASE("Chuyển đổi số nguyên (toInt)") {
        String s1("123");
        CHECK(s1.toInt() == 123);

        String s2("-456");
        CHECK(s2.toInt() == -456);

        String s3("0");
        CHECK(s3.toInt() == 0);

        String s4("abc"); // Không phải số
        CHECK(s4.toInt() == 0);
    }

    SUBCASE("Lấy chuỗi con (substring)") {
        String s("HelloWorld");
        CHECK(s.substring(0, 5) == "Hello");
        CHECK(s.substring(5, 5) == "World");
        CHECK(s.substring(5, 100) == "World"); // Count vượt quá
        CHECK(s.substring(10, 5) == "");       // Start vượt quá
    }
}
