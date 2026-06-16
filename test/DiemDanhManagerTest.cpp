#include "doctest.h"
#include "../src/DiemDanhManager.h"

TEST_CASE("DiemDanhManager - Tinh Ti Le Vang") {
    Vector<PhieuDiemDanh> dsDD;
    SinhVien sv; sv.mssv = "HE1"; sv.maLop = "SE1";

    PhieuDiemDanh p1; p1.mssv = "HE1"; p1.maLop = "SE1"; p1.ngay = "01/01/2026"; p1.trangThai = 'K';
    PhieuDiemDanh p2; p2.mssv = "HE1"; p2.maLop = "SE1"; p2.ngay = "02/01/2026"; p2.trangThai = 'P';
    PhieuDiemDanh p3; p3.mssv = "HE1"; p3.maLop = "SE1"; p3.ngay = "03/01/2026"; p3.trangThai = 'C';
    dsDD.push_back(p1);
    dsDD.push_back(p2);
    dsDD.push_back(p3);

    int tongSoBuoi = 10;
    ThongKeSinhVien tk = DiemDanhManager::tinhTiLeVang(dsDD, sv, tongSoBuoi);
    
    CHECK(tk.mssv == "HE1");
    CHECK(tk.soVang == 2);
    CHECK(tk.soVangKhongPhep == 1);
    CHECK(tk.tiLe == 20.0f); // 2/10 = 20%
    CHECK(tk.nguyCoiCamThi == false); // Chua tren 20% (chi >20% moi cam thi theo logic or >=20% tuy logic code hien tai)
}
