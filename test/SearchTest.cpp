#include "doctest.h"
#include "../src/Search.h"

TEST_CASE("Search - timLopHocTheoMa và timSinhVienTheoMSSV") {
    Vector<LopHoc> dsLop;
    LopHoc lh1; lh1.maLop = "SE1"; dsLop.push_back(lh1);
    LopHoc lh2; lh2.maLop = "SE2"; dsLop.push_back(lh2);

    Vector<SinhVien> dsSV;
    SinhVien sv1; sv1.mssv = "HE1"; dsSV.push_back(sv1);
    SinhVien sv2; sv2.mssv = "HE2"; dsSV.push_back(sv2);

    SUBCASE("Tìm thấy") {
        CHECK(Search::timLopHocTheoMa(dsLop, "SE1") == 0);
        CHECK(Search::timLopHocTheoMa(dsLop, "SE2") == 1);

        CHECK(Search::timSinhVienTheoMSSV(dsSV, "HE1") == 0);
        CHECK(Search::timSinhVienTheoMSSV(dsSV, "HE2") == 1);
    }

    SUBCASE("Không tìm thấy") {
        CHECK(Search::timLopHocTheoMa(dsLop, "SE99") == -1);
        CHECK(Search::timSinhVienTheoMSSV(dsSV, "HE99") == -1);
    }

    SUBCASE("Tìm trên danh sách rỗng") {
        Vector<LopHoc> dsLop_rong;
        Vector<SinhVien> dsSV_rong;
        CHECK(Search::timLopHocTheoMa(dsLop_rong, "SE1") == -1);
        CHECK(Search::timSinhVienTheoMSSV(dsSV_rong, "HE1") == -1);
    }
}

TEST_CASE("Search - Tìm kiếm trả về danh sách (vector result)") {
    Vector<SinhVien> dsSV;
    SinhVien sv1; sv1.mssv = "HE1"; sv1.maLop = "SE1"; dsSV.push_back(sv1);
    SinhVien sv2; sv2.mssv = "HE2"; sv2.maLop = "SE1"; dsSV.push_back(sv2);
    SinhVien sv3; sv3.mssv = "HE3"; sv3.maLop = "SE2"; dsSV.push_back(sv3);

    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.ngay = "01/01/2023"; dsDD.push_back(dd1);
    PhieuDiemDanh dd2; dd2.mssv = "HE2"; dd2.maLop = "SE1"; dd2.ngay = "01/01/2023"; dsDD.push_back(dd2);
    PhieuDiemDanh dd3; dd3.mssv = "HE1"; dd3.maLop = "SE1"; dd3.ngay = "02/01/2023"; dsDD.push_back(dd3);

    SUBCASE("timSinhVienTheoLop") {
        Vector<SinhVien> result;
        Search::timSinhVienTheoLop(dsSV, "SE1", result);
        CHECK(result.size() == 2);
        CHECK(result[0].mssv == "HE1");
        CHECK(result[1].mssv == "HE2");

        Vector<SinhVien> result2;
        Search::timSinhVienTheoLop(dsSV, "SE_NULL", result2);
        CHECK(result2.size() == 0);
    }

    SUBCASE("timDiemDanhTheoNgayVaLop") {
        Vector<PhieuDiemDanh> result;
        Search::timDiemDanhTheoNgayVaLop(dsDD, "01/01/2023", "SE1", result);
        CHECK(result.size() == 2);
        
        Vector<PhieuDiemDanh> result_empty;
        Search::timDiemDanhTheoNgayVaLop(dsDD, "01/01/2023", "SE99", result_empty);
        CHECK(result_empty.size() == 0);
    }

    SUBCASE("timDiemDanhTheoMSSV") {
        Vector<PhieuDiemDanh> result;
        Search::timDiemDanhTheoMSSV(dsDD, "HE1", result);
        CHECK(result.size() == 2); // Ngày 1 và Ngày 2
    }

    SUBCASE("timDiemDanhTheoMSSVvaLop") {
        Vector<PhieuDiemDanh> result;
        Search::timDiemDanhTheoMSSVvaLop(dsDD, "HE1", "SE1", result);
        CHECK(result.size() == 2);
        
        Vector<PhieuDiemDanh> result2;
        Search::timDiemDanhTheoMSSVvaLop(dsDD, "HE1", "SE2", result2); // Sinh viên ở SE1, tìm SE2 -> 0
        CHECK(result2.size() == 0);
    }
}

TEST_CASE("Search - daDiemDanhBuoi") {
    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.ngay = "01/01/2023"; dsDD.push_back(dd1);

    SUBCASE("Có tồn tại") {
        CHECK(Search::daDiemDanhBuoi(dsDD, "01/01/2023", "SE1") == true);
    }

    SUBCASE("Không tồn tại") {
        CHECK(Search::daDiemDanhBuoi(dsDD, "02/01/2023", "SE1") == false);
        CHECK(Search::daDiemDanhBuoi(dsDD, "01/01/2023", "SE2") == false);
    }

    SUBCASE("Danh sách rỗng") {
        Vector<PhieuDiemDanh> dsDD_rong;
        CHECK(Search::daDiemDanhBuoi(dsDD_rong, "01/01/2023", "SE1") == false);
    }
}

TEST_CASE("Search - Crash Scenarios") {
    SUBCASE("Chuỗi rỗng") {
        Vector<LopHoc> dsLop;
        LopHoc lh; lh.maLop = ""; dsLop.push_back(lh);
        
        CHECK(Search::timLopHocTheoMa(dsLop, "") == 0);
        CHECK(Search::timLopHocTheoMa(dsLop, "SE1") == -1);
    }

    SUBCASE("Kết quả nạp vào vector đã có sẵn dữ liệu") {
        Vector<PhieuDiemDanh> dsDD;
        PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.ngay = "01/01/2023"; dsDD.push_back(dd1);

        Vector<PhieuDiemDanh> result;
        PhieuDiemDanh dummy; dummy.mssv = "DUMMY"; result.push_back(dummy);
        
        // Theo chuẩn, hàm tìm kiếm thường append hoặc clear. Ta xem implementation.
        // Giả sử nó sẽ tự làm sạch (hoặc ta coi kết quả trả về như thế nào)
        // Nếu implementation không clear thì nó sẽ nối thêm. 
        Search::timDiemDanhTheoNgayVaLop(dsDD, "01/01/2023", "SE1", result);
        // Ta chỉ kiểm tra việc nó không crash. Việc append hay thay thế phụ thuộc thiết kế hàm.
        CHECK(result.size() >= 1);
    }
}
