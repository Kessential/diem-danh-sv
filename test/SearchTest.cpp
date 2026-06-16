#include "doctest.h"
#include "../src/Search.h"

TEST_CASE("Search - Tim Lop Hoc") {
    Vector<LopHoc> ds;
    LopHoc lh; lh.maLop = "SE1"; ds.push_back(lh);
    lh.maLop = "SE2"; ds.push_back(lh);
    
    CHECK(Search::timLopHocTheoMa(ds, "SE1") == 0);
    CHECK(Search::timLopHocTheoMa(ds, "SE2") == 1);
    CHECK(Search::timLopHocTheoMa(ds, "SE3") == -1);
}

TEST_CASE("Search - Tim Sinh Vien") {
    Vector<SinhVien> ds;
    SinhVien sv; sv.mssv = "HE1"; sv.maLop = "SE1"; ds.push_back(sv);
    sv.mssv = "HE2"; sv.maLop = "SE1"; ds.push_back(sv);
    sv.mssv = "HE3"; sv.maLop = "SE2"; ds.push_back(sv);

    CHECK(Search::timSinhVienTheoMSSV(ds, "HE2") == 1);
    CHECK(Search::timSinhVienTheoMSSV(ds, "HE4") == -1);

    Vector<SinhVien> rs;
    Search::timSinhVienTheoLop(ds, "SE1", rs);
    CHECK(rs.size() == 2);
    
    Search::timSinhVienTheoLop(ds, "SE3", rs);
    CHECK(rs.size() == 0);
}
