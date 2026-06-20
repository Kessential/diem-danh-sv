#include "doctest.h"
#include "../src/BaoCao.h"

TEST_CASE("BaoCao - xayDungThongKe (Theo sinh viên)") {
    Vector<LopHoc> dsLop;
    LopHoc lh; lh.maLop = "SE1"; lh.tongSoBuoi = 10; dsLop.push_back(lh);

    Vector<SinhVien> dsSV;
    SinhVien sv1; sv1.mssv = "HE1"; sv1.maLop = "SE1"; dsSV.push_back(sv1);
    SinhVien sv2; sv2.mssv = "HE2"; sv2.maLop = "SE1"; dsSV.push_back(sv2);

    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh p1; p1.mssv = "HE1"; p1.maLop = "SE1"; p1.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(p1);
    PhieuDiemDanh p2; p2.mssv = "HE1"; p2.maLop = "SE1"; p2.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(p2);
    PhieuDiemDanh p3; p3.mssv = "HE1"; p3.maLop = "SE1"; p3.trangThai = TrangThaiDD::VANG_PHEP; dsDD.push_back(p3); // HE1 vắng 3 (2 không phép, 1 có phép)

    SUBCASE("Trường hợp cơ bản (Lớp tồn tại, có sinh viên, có điểm danh)") {
        Vector<ThongKeSinhVien> result;
        ThongKeSinhVien dummy; dummy.mssv = "DUMMY"; result.push_back(dummy); // Test hàm có clear vector không

        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE1", result);

        CHECK(result.size() == 2);
        if(result.size() == 2) {
            CHECK(result[0].mssv == "HE1");
            CHECK(result[0].soVang == 3);
            CHECK(result[0].soVangKhongPhep == 2);
            CHECK(result[0].tiLeVangKP == doctest::Approx(20.0f));

            CHECK(result[1].mssv == "HE2");
            CHECK(result[1].soVang == 0);
            CHECK(result[1].tiLeVangKP == doctest::Approx(0.0f));
        }
    }

    SUBCASE("Mã lớp không tồn tại trong dsLop") {
        Vector<ThongKeSinhVien> result;
        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE999", result);
        CHECK(result.size() == 0);
    }
    
    SUBCASE("Lớp có sinh viên nhưng không có trong dsLop (Tránh crash do chia cho tongSoBuoi = 0)") {
        Vector<ThongKeSinhVien> result;
        SinhVien sv3; sv3.mssv = "HE3"; sv3.maLop = "SE2"; dsSV.push_back(sv3);
        
        // Gọi hàm cho "SE2" - không có trong dsLop nên không tìm thấy lớp (tongSoBuoi = 0)
        BaoCao::xayDungThongKe(dsSV, dsDD, dsLop, "SE2", result);
        CHECK(result.size() == 1);
        if(result.size() == 1) {
            CHECK(result[0].mssv == "HE3");
            CHECK(result[0].tiLeVangKP == doctest::Approx(0.0f));
        }
    }

    SUBCASE("Danh sách sinh viên rỗng") {
        Vector<ThongKeSinhVien> result;
        Vector<SinhVien> dsSV_rong;
        BaoCao::xayDungThongKe(dsSV_rong, dsDD, dsLop, "SE1", result);
        CHECK(result.size() == 0);
    }

    SUBCASE("Danh sách phiếu điểm danh rỗng") {
        Vector<ThongKeSinhVien> result;
        Vector<PhieuDiemDanh> dsDD_rong;
        BaoCao::xayDungThongKe(dsSV, dsDD_rong, dsLop, "SE1", result);
        CHECK(result.size() == 2);
        CHECK(result[0].soVang == 0);
        CHECK(result[1].soVang == 0);
    }
}

// Lưu ý: Các hàm in/xuất giao diện trực tiếp như inBaoCaoTheoLop, inBaoCaoTungSinhVien
// Không nên test tự động do chúng gọi cout và giao tiếp người dùng.
// Chúng chỉ gọi hai hàm xây dựng thống kê đã được test kỹ ở trên.
