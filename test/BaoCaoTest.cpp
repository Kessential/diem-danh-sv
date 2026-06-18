#include "doctest.h"
#include "../src/BaoCao.h"

TEST_CASE("BaoCao - Xay Dung Thong Ke") {
    Vector<LopHoc> dsLop;
    LopHoc lh; lh.maLop = "SE1"; lh.tongSoBuoi = 10; dsLop.push_back(lh);

    Vector<SinhVien> dsSV;
    SinhVien sv1; sv1.mssv = "HE1"; sv1.maLop = "SE1"; dsSV.push_back(sv1);
    SinhVien sv2; sv2.mssv = "HE2"; sv2.maLop = "SE1"; dsSV.push_back(sv2);

    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh p1; p1.mssv = "HE1"; p1.maLop = "SE1"; p1.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(p1);
    PhieuDiemDanh p2; p2.mssv = "HE1"; p2.maLop = "SE1"; p2.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(p2);
    PhieuDiemDanh p3; p3.mssv = "HE1"; p3.maLop = "SE1"; p3.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(p3); // HE1 vang 3

    SUBCASE("Truong hop co ban") {
        Vector<ThongKeSinhVien> result;
        // pre-fill result to ensure it gets cleared
        ThongKeSinhVien dummy; dummy.mssv = "DUMMY"; result.push_back(dummy);

        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE1", result);

        CHECK(result.size() == 2);
        if(result.size() == 2) {
            CHECK(result[0].mssv == "HE1");
            CHECK(result[0].soVang == 3);
            CHECK(result[0].tiLe == doctest::Approx(30.0f));

            CHECK(result[1].mssv == "HE2");
            CHECK(result[1].soVang == 0);
            CHECK(result[1].tiLe == doctest::Approx(0.0f));
        }
    }

    SUBCASE("Ma lop khong ton tai trong dsLop") {
        Vector<ThongKeSinhVien> result;
        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE999", result);
        CHECK(result.size() == 0);
    }
    
    SUBCASE("Ma lop ton tai trong dsSV nhung khong trong dsLop (kiem tra crash do chia 0)") {
        Vector<ThongKeSinhVien> result;
        SinhVien sv3; sv3.mssv = "HE3"; sv3.maLop = "SE2"; dsSV.push_back(sv3);
        
        // Goi ham cho "SE2" - khong co trong dsLop nen tongSoBuoi = 0
        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE2", result);
        
        CHECK(result.size() == 1);
        if(result.size() == 1) {
            CHECK(result[0].mssv == "HE3");
            CHECK(result[0].soVang == 0);
            CHECK(result[0].tiLe == doctest::Approx(0.0f)); // Khong bi chia cho 0
        }
    }

    SUBCASE("Danh sach sinh vien rong") {
        Vector<ThongKeSinhVien> result;
        Vector<SinhVien> dsSV_rong;
        BaoCao::xayDungThongKe(dsSV_rong, dsDD, dsLop, "SE1", result);
        CHECK(result.size() == 0);
    }

    SUBCASE("Danh sach phieu diem danh rong") {
        Vector<ThongKeSinhVien> result;
        Vector<PhieuDiemDanh> dsDD_rong;
        BaoCao::xayDungThongKe(dsSV, dsDD_rong, dsLop, "SE1", result);
        CHECK(result.size() == 2);
        if(result.size() == 2) {
            CHECK(result[0].mssv == "HE1");
            CHECK(result[0].soVang == 0);
            CHECK(result[1].mssv == "HE2");
            CHECK(result[1].soVang == 0);
        }
    }

    SUBCASE("Sinh vien co phieu diem danh nhung o lop khac") {
        Vector<ThongKeSinhVien> result;
        PhieuDiemDanh p_other; p_other.mssv = "HE1"; p_other.maLop = "SE2"; p_other.trangThai = TrangThaiDD::VANG_KHONG_PHEP;
        dsDD.push_back(p_other);

        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE1", result);
        
        CHECK(result.size() == 2);
        if(result.size() == 2) {
            CHECK(result[0].mssv == "HE1");
            CHECK(result[0].soVang == 3); // Van la 3, vi phieu kia o lop SE2
        }
    }

    SUBCASE("Vang phep va vang khong phep") {
        Vector<ThongKeSinhVien> result;
        PhieuDiemDanh p_phep; p_phep.mssv = "HE2"; p_phep.maLop = "SE1"; p_phep.trangThai = TrangThaiDD::VANG_PHEP;
        dsDD.push_back(p_phep);
        PhieuDiemDanh p_kphep; p_kphep.mssv = "HE2"; p_kphep.maLop = "SE1"; p_kphep.trangThai = TrangThaiDD::VANG_KHONG_PHEP;
        dsDD.push_back(p_kphep);

        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE1", result);
        
        CHECK(result.size() == 2);
        if(result.size() == 2) {
            CHECK(result[1].mssv == "HE2");
            CHECK(result[1].soVang == 2); // 1 vang phep + 1 vang khong phep
            CHECK(result[1].soVangKhongPhep == 1);
            CHECK(result[1].tiLe == doctest::Approx(10.0f)); // 1 vang khong phep / 10 buoi = 10%
        }
    }
}
