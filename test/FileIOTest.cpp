#include "doctest.h"
#include "../src/FileIO.h"
#include <cstdio>
#include <fstream>

TEST_CASE("FileIO - Load and Save LopHoc") {
    Vector<LopHoc> ds;
    LopHoc lh;
    lh.maLop = "TEST1";
    lh.tenLop = "Kiem thu";
    lh.giangVien = "Nguyen Van A";
    lh.tkb.thu = 2; lh.tkb.tietBatDau = 1; lh.tkb.soTiet = 2; lh.tkb.phong = "A101";
    lh.tongSoBuoi = 10;
    ds.push_back(lh);

    const char* testFile = "test_lophoc.txt";
    FileIO::saveLopHoc(testFile, ds);

    Vector<LopHoc> dsLoad;
    bool success = FileIO::loadLopHoc(testFile, dsLoad);
    CHECK(success == true);
    CHECK(dsLoad.size() == 1);
    if(dsLoad.size() == 1) {
        CHECK(dsLoad[0].maLop == "TEST1");
        CHECK(dsLoad[0].giangVien == "Nguyen Van A");
    }
    
    std::remove(testFile);
}
