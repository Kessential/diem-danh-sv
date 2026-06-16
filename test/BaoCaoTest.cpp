#include "doctest.h"
#include "../src/BaoCao.h"

TEST_CASE("BaoCao - Xay Dung Thong Ke") {
    Vector<LopHoc> dsLop;
    LopHoc lh; lh.maLop = "SE1"; lh.tongSoBuoi = 10; dsLop.push_back(lh);

    Vector<SinhVien> dsSV;
    SinhVien sv1; sv1.mssv = "HE1"; sv1.maLop = "SE1"; dsSV.push_back(sv1);
    SinhVien sv2; sv2.mssv = "HE2"; sv2.maLop = "SE1"; dsSV.push_back(sv2);

    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh p1; p1.mssv = "HE1"; p1.maLop = "SE1"; p1.trangThai = 'K'; dsDD.push_back(p1);
    PhieuDiemDanh p2; p2.mssv = "HE1"; p2.maLop = "SE1"; p2.trangThai = 'K'; dsDD.push_back(p2);
    PhieuDiemDanh p3; p3.mssv = "HE1"; p3.maLop = "SE1"; p3.trangThai = 'K'; dsDD.push_back(p3); // HE1 vang 3

    Vector<ThongKeSinhVien> result;
    BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE1", result);

    CHECK(result.size() == 2);
    if(result.size() == 2) {
        CHECK(result[0].mssv == "HE1");
        CHECK(result[0].soVang == 3);
        CHECK(result[0].tiLe == doctest::Approx(30.0f));

        CHECK(result[1].mssv == "HE2");
        CHECK(result[1].soVang == 0);
    }
}
