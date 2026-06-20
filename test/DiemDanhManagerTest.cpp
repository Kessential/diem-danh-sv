#include "doctest.h"
#include "../src/DiemDanhManager.h"

TEST_CASE("DiemDanhManager - tinhTiLeVang") {
    Vector<PhieuDiemDanh> dsDD;
    SinhVien sv; sv.mssv = "HE1"; sv.hoTen = "Nguyen A"; sv.maLop = "SE1";

    SUBCASE("Không có buổi học nào (tongSoBuoi = 0) -> tránh chia 0") {
        ThongKeSinhVien tk = DiemDanhManager::tinhTiLeVang(dsDD, sv, 0);
        CHECK(tk.mssv == "HE1");
        CHECK(tk.soVang == 0);
        CHECK(tk.soVangKhongPhep == 0);
        CHECK(tk.tiLeVangKP == doctest::Approx(0.0f));
        CHECK(tk.nguyCoCamThi == false);
    }

    SUBCASE("Không vắng buổi nào") {
        PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.trangThai = TrangThaiDD::CO_MAT;
        dsDD.push_back(dd1);

        ThongKeSinhVien tk = DiemDanhManager::tinhTiLeVang(dsDD, sv, 10);
        CHECK(tk.soVang == 0);
        CHECK(tk.tiLeVangKP == doctest::Approx(0.0f));
        CHECK(tk.nguyCoCamThi == false);
    }

    SUBCASE("Có vắng phép và không phép") {
        PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.trangThai = TrangThaiDD::VANG_PHEP; dsDD.push_back(dd1);
        PhieuDiemDanh dd2; dd2.mssv = "HE1"; dd2.maLop = "SE1"; dd2.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(dd2);
        PhieuDiemDanh dd3; dd3.mssv = "HE1"; dd3.maLop = "SE1"; dd3.trangThai = TrangThaiDD::VANG_KHONG_PHEP; dsDD.push_back(dd3);

        ThongKeSinhVien tk = DiemDanhManager::tinhTiLeVang(dsDD, sv, 10);
        CHECK(tk.soVang == 3);
        CHECK(tk.soVangKhongPhep == 2);
        CHECK(tk.tiLeVangKP == doctest::Approx(20.0f)); 
        CHECK(tk.nguyCoCamThi == true); // KP >= 20% → canh bao
    }
}

TEST_CASE("DiemDanhManager - suaDiemDanh") {
    Vector<PhieuDiemDanh> dsDD;
    PhieuDiemDanh dd1; dd1.mssv = "HE1"; dd1.maLop = "SE1"; dd1.ngay = "01/01/2023"; dd1.trangThai = TrangThaiDD::CO_MAT;
    dsDD.push_back(dd1);

    SUBCASE("Sửa thành công khi tồn tại") {
        bool res = DiemDanhManager::suaDiemDanh(dsDD, "HE1", "SE1", "01/01/2023", TrangThaiDD::VANG_PHEP);
        CHECK(res == true);
        CHECK(dsDD[0].trangThai == TrangThaiDD::VANG_PHEP);
    }

    SUBCASE("Không tìm thấy sinh viên/ngày/lớp tương ứng") {
        bool res = DiemDanhManager::suaDiemDanh(dsDD, "HE99", "SE1", "01/01/2023", TrangThaiDD::VANG_PHEP);
        CHECK(res == false);
        CHECK(dsDD[0].trangThai == TrangThaiDD::CO_MAT); // Không đổi
    }

    SUBCASE("Sửa thành trạng thái giống hệt") {
        bool res = DiemDanhManager::suaDiemDanh(dsDD, "HE1", "SE1", "01/01/2023", TrangThaiDD::CO_MAT);
        CHECK(res == true); // Vẫn báo true (tìm thấy)
        CHECK(dsDD[0].trangThai == TrangThaiDD::CO_MAT);
    }
}

// Lưu ý: Hàm ghiDiemDanhMoiLop và kiemTraCanhBaoCamThi tương tác với console in/out.
// Để tránh block unit tests do lệnh std::cin, hai hàm này bị loại trừ ở đây.
