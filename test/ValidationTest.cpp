#include "doctest.h"
#include "../src/Validation.h"

TEST_CASE("Validation - isValidDate") {
    SUBCASE("Định dạng chuẩn (DD/MM/YYYY) và logic đúng") {
        CHECK(Validation::isValidDate("01/01/2023") == true);
        CHECK(Validation::isValidDate("31/12/2023") == true);
        CHECK(Validation::isValidDate("29/02/2020") == true); // Năm nhuận
        CHECK(Validation::isValidDate("28/02/2023") == true); // Không nhuận
    }

    SUBCASE("Định dạng sai (Độ dài, ký tự)") {
        CHECK(Validation::isValidDate("1/1/2023") == false);    // Thiếu số 0
        CHECK(Validation::isValidDate("01-01-2023") == false);  // Sai dấu phân cách
        CHECK(Validation::isValidDate("01/01/23") == false);    // Sai số lượng YYYY
        CHECK(Validation::isValidDate("abcdefghij") == false);  // Chữ
        CHECK(Validation::isValidDate("") == false);            // Chuỗi rỗng
    }

    SUBCASE("Logic sai (Ngày tháng không tồn tại)") {
        CHECK(Validation::isValidDate("32/01/2023") == false);  // Ngày > 31
        CHECK(Validation::isValidDate("00/01/2023") == false);  // Ngày 0
        CHECK(Validation::isValidDate("15/13/2023") == false);  // Tháng > 12
        CHECK(Validation::isValidDate("15/00/2023") == false);  // Tháng 0
        CHECK(Validation::isValidDate("31/04/2023") == false);  // Tháng 4 chỉ có 30 ngày
        CHECK(Validation::isValidDate("29/02/2023") == false);  // 2023 không nhuận
        CHECK(Validation::isValidDate("01/01/0000") == false);  // Năm 0 tùy implementation, nhưng thường bắt > 0
    }
}

TEST_CASE("Validation - isValidMSSV") {
    SUBCASE("Hợp lệ") {
        CHECK(Validation::isValidMSSV("HE1") == true);
        CHECK(Validation::isValidMSSV("HE123456") == true);
        CHECK(Validation::isValidMSSV("123456") == true); // Toàn số
        CHECK(Validation::isValidMSSV("ABCDEF") == true); // Toàn chữ
    }

    SUBCASE("Không hợp lệ") {
        CHECK(Validation::isValidMSSV("HE_1") == false); // Ký tự đặc biệt
        CHECK(Validation::isValidMSSV("HE 1") == false); // Dấu cách
        CHECK(Validation::isValidMSSV("HE@1") == false); 
        CHECK(Validation::isValidMSSV("") == false);     // Rỗng
    }

    SUBCASE("Độ dài") {
        String long_mssv("123456789012345678901"); // 21 ký tự
        CHECK(Validation::isValidMSSV(long_mssv) == false); // Giới hạn là 20
        
        String valid_length("12345678901234567890"); // 20 ký tự
        CHECK(Validation::isValidMSSV(valid_length) == true);
    }
}

TEST_CASE("Validation - isValidTrangThai") {
    SUBCASE("Hợp lệ") {
        CHECK(Validation::isValidTrangThai('C') == true);
        CHECK(Validation::isValidTrangThai('P') == true);
        CHECK(Validation::isValidTrangThai('K') == true);
    }

    SUBCASE("Không hợp lệ") {
        CHECK(Validation::isValidTrangThai('c') == false); // Thường phân biệt hoa thường
        CHECK(Validation::isValidTrangThai('X') == false);
        CHECK(Validation::isValidTrangThai(' ') == false);
        CHECK(Validation::isValidTrangThai('\0') == false);
    }
}

TEST_CASE("Validation - isValidMaLop") {
    SUBCASE("Hợp lệ") {
        CHECK(Validation::isValidMaLop("SE1") == true);
        CHECK(Validation::isValidMaLop("A") == true);
    }

    SUBCASE("Không hợp lệ") {
        CHECK(Validation::isValidMaLop("") == false); // Rỗng không được
        
        // Quá độ dài (giới hạn 50)
        String long_class("123456789012345678901234567890123456789012345678901"); // 51 ký tự
        CHECK(Validation::isValidMaLop(long_class) == false);
        
        String max_class("12345678901234567890123456789012345678901234567890"); // 50 ký tự
        CHECK(Validation::isValidMaLop(max_class) == true);
    }
}

// Lưu ý: Các hàm như nhapChuoi, nhapSoNguyen, nhapXacNhan yêu cầu input từ user (std::cin).
// Không nên test trong unit tests chạy tự động vì sẽ gây block (treo).
// Nếu muốn test cần dùng cơ chế mock std::cin/std::cout.
