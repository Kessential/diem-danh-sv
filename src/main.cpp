// ============================================================
//  main.cpp — Điểm vào chương trình
//  Hệ thống Quản lý Điểm danh Lớp học
// ============================================================

#include "Vector.h"
#include "CustomString.h"
#include "Models.h"
#include "FileIO.h"
#include "Menu.h"
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    // ── 1. Khai báo 3 mảng động toàn phiên làm việc ──────────
    Vector<LopHoc>        dsLopHoc;
    Vector<SinhVien>      dsSinhVien;
    Vector<PhieuDiemDanh> dsDiemDanh;

    // ── 2. Nạp dữ liệu từ file khi khởi động ─────────────────
    if (!FileIO::loadLopHoc(PATH_LOPHOC, dsLopHoc)) {
        printf("[INFO] Khong doc duoc '%s', bat dau voi danh sach rong.\n",
               PATH_LOPHOC);
    }
    if (!FileIO::loadSinhVien(PATH_SINHVIEN, dsSinhVien)) {
        printf("[INFO] Khong doc duoc '%s', bat dau voi danh sach rong.\n",
               PATH_SINHVIEN);
    }
    if (!FileIO::loadDiemDanh(PATH_DIEMDANH, dsDiemDanh)) {
        printf("[INFO] Khong doc duoc '%s', bat dau voi danh sach rong.\n",
               PATH_DIEMDANH);
    }

    printf("\n  [OK] Nap du lieu thanh cong:\n");
    printf("       Lop hoc  : %d\n", (int)dsLopHoc.size());
    printf("       Sinh vien: %d\n", (int)dsSinhVien.size());
    printf("       Diem danh: %d phieu\n\n", (int)dsDiemDanh.size());

    // ── 3. Vòng lặp menu chính ────────────────────────────────
    int luaChon;
    do {
        hienThiMenuChinh();
        luaChon = Validation::nhapSoNguyen("  Chon chuc nang", 0, 5);
        switch (luaChon) {
            case 1: menuQuanLyLopHoc(dsLopHoc); break;
            case 2: menuQuanLySinhVien(dsSinhVien, dsLopHoc); break;
            case 3: menuDiemDanh(dsLopHoc, dsSinhVien, dsDiemDanh); break;
            case 4: menuTimKiem(dsLopHoc, dsSinhVien, dsDiemDanh); break;
            case 5: menuBaoCao(dsLopHoc, dsSinhVien, dsDiemDanh); break;
            case 0:
                printf("\n  Tam biet! Hen gap lai.\n\n");
                break;
        }
    } while (luaChon != 0);

    // ── 4. Giải phóng bộ nhớ ─────────────────────────────────
    // CustomVector destructor tự gọi delete[] khi ra khỏi scope
    return 0;
}
