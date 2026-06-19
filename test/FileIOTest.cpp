#include "doctest.h"
#include "../src/FileIO.h"
#include <cstdio> // for remove()

TEST_CASE("FileIO - splitLine") {
    SUBCASE("Chuỗi bình thường") {
        Vector<String> parts;
        FileIO::splitLine("A|B|C", '|', parts);
        CHECK(parts.size() == 3);
        CHECK(parts[0] == "A");
        CHECK(parts[1] == "B");
        CHECK(parts[2] == "C");
    }

    SUBCASE("Không có delimiter") {
        Vector<String> parts;
        FileIO::splitLine("ABC", '|', parts);
        CHECK(parts.size() == 1);
        CHECK(parts[0] == "ABC");
    }

    SUBCASE("Chuỗi rỗng") {
        Vector<String> parts;
        FileIO::splitLine("", '|', parts);
        CHECK(parts.size() == 1); // Theo logic thường trả về 1 phần tử rỗng
        CHECK(parts[0] == "");
    }

    SUBCASE("Delimiter liên tiếp hoặc ở đầu/cuối") {
        Vector<String> parts;
        FileIO::splitLine("|A||B|", '|', parts);
        CHECK(parts.size() == 5);
        CHECK(parts[0] == "");
        CHECK(parts[1] == "A");
        CHECK(parts[2] == "");
        CHECK(parts[3] == "B");
        CHECK(parts[4] == "");
    }
}

TEST_CASE("FileIO - Load từ file không tồn tại") {
    Vector<LopHoc> dsLop;
    CHECK(FileIO::loadLopHoc("non_existent_file.txt", dsLop) == false);
    CHECK(dsLop.size() == 0);
}

TEST_CASE("FileIO - Ghi và Đọc file (LopHoc)") {
    const char* test_file = "test_lophoc.txt";
    
    Vector<LopHoc> dsLop_ghi;
    LopHoc lh; 
    lh.maLop = "SE1"; lh.tenLop = "Software"; lh.giangVien = "GV1"; 
    lh.tkb.thu = 2; lh.tkb.tietBatDau = 1; lh.tkb.soTiet = 2; lh.tkb.phong = "101";
    lh.tongSoBuoi = 10;
    dsLop_ghi.push_back(lh);
    
    // Test Ghi
    CHECK(FileIO::saveLopHoc(test_file, dsLop_ghi) == true);
    
    // Test Đọc
    Vector<LopHoc> dsLop_doc;
    CHECK(FileIO::loadLopHoc(test_file, dsLop_doc) == true);
    CHECK(dsLop_doc.size() == 1);
    CHECK(dsLop_doc[0].maLop == "SE1");
    CHECK(dsLop_doc[0].tenLop == "Software");
    CHECK(dsLop_doc[0].tkb.thu == 2);
    
    // Dọn dẹp
    std::remove(test_file);
}

TEST_CASE("FileIO - Ghi và Đọc file (SinhVien)") {
    const char* test_file = "test_sinhvien.txt";
    
    Vector<SinhVien> dsSV_ghi;
    SinhVien sv; sv.mssv = "HE1"; sv.hoTen = "Nguyen Van A"; sv.maLop = "SE1";
    dsSV_ghi.push_back(sv);
    
    CHECK(FileIO::saveSinhVien(test_file, dsSV_ghi) == true);
    
    Vector<SinhVien> dsSV_doc;
    CHECK(FileIO::loadSinhVien(test_file, dsSV_doc) == true);
    CHECK(dsSV_doc.size() == 1);
    CHECK(dsSV_doc[0].mssv == "HE1");
    CHECK(dsSV_doc[0].hoTen == "Nguyen Van A");
    
    std::remove(test_file);
}

TEST_CASE("FileIO - Ghi, Đọc, và Append file (PhieuDiemDanh)") {
    const char* test_file = "test_diemdanh.txt";
    
    Vector<PhieuDiemDanh> dsDD_ghi;
    PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.ngay = "01/01/2023"; dd1.trangThai = TrangThaiDD::CO_MAT;
    dsDD_ghi.push_back(dd1);
    
    CHECK(FileIO::saveDiemDanh(test_file, dsDD_ghi) == true);
    
    // Test Append
    PhieuDiemDanh dd2; dd2.mssv = "HE2"; dd2.maLop = "SE1"; dd2.ngay = "01/01/2023"; dd2.trangThai = TrangThaiDD::VANG_PHEP;
    CHECK(FileIO::appendDiemDanh(test_file, dd2) == true);
    
    // Test Đọc
    Vector<PhieuDiemDanh> dsDD_doc;
    CHECK(FileIO::loadDiemDanh(test_file, dsDD_doc) == true);
    CHECK(dsDD_doc.size() == 2);
    CHECK(dsDD_doc[0].mssv == "HE1");
    CHECK(dsDD_doc[1].mssv == "HE2");
    CHECK(dsDD_doc[1].trangThai == TrangThaiDD::VANG_PHEP);
    
    std::remove(test_file);
}
