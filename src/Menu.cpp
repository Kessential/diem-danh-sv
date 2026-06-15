#include "Menu.h"
#include <cstdio>

void inTieuDe(const char* title) {
    printf("\n");
    printf("  ╔══════════════════════════════════════════════╗\n");
    printf("  ║  %-44s║\n", title);
    printf("  ╚══════════════════════════════════════════════╝\n");
}

void inSeparator() {
    printf("  ────────────────────────────────────────────────\n");
}

void hienThiDanhSachLop(Vector<LopHoc>& dsLop) {
    if (dsLop.size() == 0) {
        printf("  Chua co lop hoc nao.\n");
        return;
    }
    printf("  %-10s %-25s %-20s %4s %6s %5s %-10s %6s\n",
           "Ma Lop", "Ten Mon", "Giang Vien", "Thu", "TietBD", "STiet",
           "Phong", "SBuoi");
    inSeparator();
    for (int i = 0; i < (int)dsLop.size(); ++i) {
        LopHoc& lh = dsLop[i];
        printf("  %-10s %-25s %-20s %4d %6d %5d %-10s %6d\n",
               lh.maLop.c_str(), lh.tenLop.c_str(), lh.giangVien.c_str(),
               lh.tkb.thu, lh.tkb.tietBatDau, lh.tkb.soTiet,
               lh.tkb.phong.c_str(), lh.tongSoBuoi);
    }
}

void themLopHoc(Vector<LopHoc>& dsLop) {
    LopHoc lh;
    printf("\n  --- THEM LOP HOC MOI ---\n");
    Validation::nhapChuoi("  Ma lop", lh.maLop);
    if (Search::timLopHocTheoMa(dsLop, lh.maLop) != -1) {
        printf("  [!] Ma lop '%s' da ton tai!\n", lh.maLop.c_str());
        return;
    }
    Validation::nhapChuoi("  Ten mon hoc", lh.tenLop);
    Validation::nhapChuoi("  Giang vien", lh.giangVien);
    lh.tkb.thu        = Validation::nhapSoNguyen("  Thu (2-7)", 2, 7);
    lh.tkb.tietBatDau = Validation::nhapSoNguyen("  Tiet bat dau (1-12)", 1, 12);
    lh.tkb.soTiet     = Validation::nhapSoNguyen("  So tiet", 1, 6);
    Validation::nhapChuoi("  Phong hoc", lh.tkb.phong);
    lh.tongSoBuoi     = Validation::nhapSoNguyen("  Tong so buoi", 1, 60);
    dsLop.push_back(lh);
    FileIO::saveLopHoc(PATH_LOPHOC, dsLop);
    printf("  [OK] Da them lop '%s'.\n", lh.maLop.c_str());
}

void suaLopHoc(Vector<LopHoc>& dsLop) {
    String maLop;
    printf("\n  --- SUA THONG TIN LOP HOC ---\n");
    Validation::nhapChuoi("  Ma lop can sua", maLop);
    int idx = Search::timLopHocTheoMa(dsLop, maLop);
    if (idx == -1) {
        printf("  [!] Khong tim thay lop '%s'.\n", maLop.c_str());
        return;
    }
    LopHoc& lh = dsLop[idx];
    printf("  (De trong de giu nguyen gia tri hien tai)\n");
    Validation::nhapChuoi("  Ten mon hoc moi", lh.tenLop);
    Validation::nhapChuoi("  Giang vien moi", lh.giangVien);
    lh.tkb.thu        = Validation::nhapSoNguyen("  Thu (2-7)", 2, 7);
    lh.tkb.tietBatDau = Validation::nhapSoNguyen("  Tiet bat dau", 1, 12);
    lh.tkb.soTiet     = Validation::nhapSoNguyen("  So tiet", 1, 6);
    Validation::nhapChuoi("  Phong hoc", lh.tkb.phong);
    lh.tongSoBuoi     = Validation::nhapSoNguyen("  Tong so buoi", 1, 60);
    FileIO::saveLopHoc(PATH_LOPHOC, dsLop);
    printf("  [OK] Da cap nhat lop '%s'.\n", maLop.c_str());
}

void xoaLopHoc(Vector<LopHoc>& dsLop) {
    String maLop;
    printf("\n  --- XOA LOP HOC ---\n");
    Validation::nhapChuoi("  Ma lop can xoa", maLop);
    bool timThay = false;
    Vector<LopHoc> temp;
    for (int i = 0; i < (int)dsLop.size(); ++i) {
        if (dsLop[i].maLop == maLop) { timThay = true; continue; }
        temp.push_back(dsLop[i]);
    }
    if (!timThay) {
        printf("  [!] Khong tim thay lop '%s'.\n", maLop.c_str());
        return;
    }
    dsLop = temp;
    FileIO::saveLopHoc(PATH_LOPHOC, dsLop);
    printf("  [OK] Da xoa lop '%s'.\n", maLop.c_str());
}

void menuQuanLyLopHoc(Vector<LopHoc>& dsLop) {
    int chon;
    do {
        inTieuDe("1. QUAN LY LOP HOC");
        printf("    1. Xem danh sach lop hoc\n");
        printf("    2. Them lop hoc moi\n");
        printf("    3. Sua thong tin lop hoc\n");
        printf("    4. Xoa lop hoc\n");
        printf("    0. Quay lai menu chinh\n");
        inSeparator();
        chon = Validation::nhapSoNguyen("  Chon", 0, 4);
        switch (chon) {
            case 1: hienThiDanhSachLop(dsLop); break;
            case 2: themLopHoc(dsLop); break;
            case 3: suaLopHoc(dsLop); break;
            case 4: xoaLopHoc(dsLop); break;
        }
    } while (chon != 0);
}

void hienThiSVTheoLop(Vector<SinhVien>& dsSV, const String& maLop) {
    printf("\n  Danh sach sinh vien lop %s:\n", maLop.c_str());
    printf("  %-12s %-30s\n", "MSSV", "Ho Ten");
    inSeparator();
    int dem = 0;
    for (int i = 0; i < (int)dsSV.size(); ++i) {
        if (dsSV[i].maLop == maLop) {
            printf("  %-12s %-30s\n", dsSV[i].mssv.c_str(), dsSV[i].hoTen.c_str());
            ++dem;
        }
    }
    if (dem == 0) printf("  (Khong co sinh vien nao)\n");
    else printf("\n  Tong cong: %d sinh vien.\n", dem);
}

void themSinhVien(Vector<SinhVien>& dsSV, Vector<LopHoc>& dsLop) {
    SinhVien sv;
    printf("\n  --- THEM SINH VIEN ---\n");
    Validation::nhapChuoi("  MSSV", sv.mssv);
    if (!Validation::isValidMSSV(sv.mssv)) {
        printf("  [!] MSSV khong hop le.\n"); return;
    }
    if (Search::timSinhVienTheoMSSV(dsSV, sv.mssv) != -1) {
        printf("  [!] MSSV '%s' da ton tai!\n", sv.mssv.c_str()); return;
    }
    Validation::nhapChuoi("  Ho Ten", sv.hoTen);
    Validation::nhapChuoi("  Ma Lop", sv.maLop);
    if (Search::timLopHocTheoMa(dsLop, sv.maLop) == -1) {
        printf("  [!] Ma lop '%s' khong ton tai!\n", sv.maLop.c_str()); return;
    }
    dsSV.push_back(sv);
    FileIO::saveSinhVien(PATH_SINHVIEN, dsSV);
    printf("  [OK] Da them sinh vien '%s'.\n", sv.mssv.c_str());
}

void suaSinhVien(Vector<SinhVien>& dsSV) {
    String mssv;
    printf("\n  --- SUA THONG TIN SINH VIEN ---\n");
    Validation::nhapChuoi("  MSSV can sua", mssv);
    int idx = Search::timSinhVienTheoMSSV(dsSV, mssv);
    if (idx == -1) {
        printf("  [!] Khong tim thay MSSV '%s'.\n", mssv.c_str()); return;
    }
    Validation::nhapChuoi("  Ho Ten moi", dsSV[idx].hoTen);
    FileIO::saveSinhVien(PATH_SINHVIEN, dsSV);
    printf("  [OK] Da cap nhat sinh vien '%s'.\n", mssv.c_str());
}

void xoaSinhVien(Vector<SinhVien>& dsSV) {
    String mssv;
    printf("\n  --- XOA SINH VIEN ---\n");
    Validation::nhapChuoi("  MSSV can xoa", mssv);
    bool timThay = false;
    Vector<SinhVien> temp;
    for (int i = 0; i < (int)dsSV.size(); ++i) {
        if (dsSV[i].mssv == mssv) { timThay = true; continue; }
        temp.push_back(dsSV[i]);
    }
    if (!timThay) { printf("  [!] Khong tim thay '%s'.\n", mssv.c_str()); return; }
    dsSV = temp;
    FileIO::saveSinhVien(PATH_SINHVIEN, dsSV);
    printf("  [OK] Da xoa sinh vien '%s'.\n", mssv.c_str());
}

void menuQuanLySinhVien(Vector<SinhVien>& dsSV, Vector<LopHoc>& dsLop) {
    int chon;
    do {
        inTieuDe("2. QUAN LY SINH VIEN");
        printf("    1. Xem danh sach SV theo lop\n");
        printf("    2. Them sinh vien vao lop\n");
        printf("    3. Sua thong tin sinh vien\n");
        printf("    4. Xoa sinh vien khoi lop\n");
        printf("    0. Quay lai menu chinh\n");
        inSeparator();
        chon = Validation::nhapSoNguyen("  Chon", 0, 4);
        switch (chon) {
            case 1: {
                String maLop;
                Validation::nhapChuoi("  Ma lop", maLop);
                hienThiSVTheoLop(dsSV, maLop);
                break;
            }
            case 2: themSinhVien(dsSV, dsLop); break;
            case 3: suaSinhVien(dsSV); break;
            case 4: xoaSinhVien(dsSV); break;
        }
    } while (chon != 0);
}

void menuDiemDanh(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD) {
    int chon;
    do {
        inTieuDe("3. DIEM DANH");
        printf("    1. Ghi nhan diem danh buoi hoc moi\n");
        printf("    2. Xem/Sua diem danh theo ngay + lop\n");
        printf("    3. Kiem tra canh bao cam thi (ca lop)\n");
        printf("    0. Quay lai menu chinh\n");
        inSeparator();
        chon = Validation::nhapSoNguyen("  Chon", 0, 3);
        switch (chon) {
            case 1: {
                String maLop, ngay;
                Validation::nhapChuoi("  Ma lop", maLop);
                do {
                    Validation::nhapChuoi("  Ngay diem danh (DD/MM/YYYY)", ngay);
                } while (!Validation::isValidDate(ngay));
                DiemDanhManager::ghiDiemDanhMoiLop(dsSV, dsDD, maLop, ngay);
                FileIO::saveDiemDanh(PATH_DIEMDANH, dsDD);
                break;
            }
            case 2: {
                String maLop, ngay;
                Validation::nhapChuoi("  Ma lop", maLop);
                do {
                    Validation::nhapChuoi("  Ngay (DD/MM/YYYY)", ngay);
                } while (!Validation::isValidDate(ngay));
                Vector<PhieuDiemDanh> result;
                Search::timDiemDanhTheoNgayVaLop(dsDD, ngay, maLop, result);
                if (result.size() == 0) {
                    printf("  Khong co du lieu diem danh ngay %s lop %s.\n",
                           ngay.c_str(), maLop.c_str());
                    break;
                }
                printf("  %-12s %-30s %s\n", "MSSV", "Ho Ten", "Trang thai");
                inSeparator();
                for (int i = 0; i < (int)result.size(); ++i) {
                    int idx = Search::timSinhVienTheoMSSV(dsSV, result[i].mssv);
                    const char* ten = (idx >= 0) ? dsSV[idx].hoTen.c_str() : "?";
                    const char* ttStr =
                        result[i].trangThai == 'C' ? "Co mat" :
                        result[i].trangThai == 'P' ? "Vang co phep" : "Vang khong phep";
                    printf("  %-12s %-30s %s\n",
                           result[i].mssv.c_str(), ten, ttStr);
                }
                printf("\n  Ban co muon sua diem danh? (y/n): ");
                char c; scanf(" %c", &c);
                int cc; while ((cc = getchar()) != '\n' && cc != EOF);
                if (c == 'y' || c == 'Y') {
                    String mssv;
                    Validation::nhapChuoi("  MSSV can sua", mssv);
                    char ttMoi = Validation::nhapTrangThai(mssv.c_str());
                    if (DiemDanhManager::suaDiemDanh(dsDD, mssv, maLop, ngay, ttMoi)) {
                        FileIO::saveDiemDanh(PATH_DIEMDANH, dsDD);
                        printf("  [OK] Da cap nhat diem danh.\n");
                    } else {
                        printf("  [!] Khong tim thay phieu diem danh.\n");
                    }
                }
                break;
            }
            case 3: {
                String maLop;
                Validation::nhapChuoi("  Ma lop", maLop);
                DiemDanhManager::kiemTraCanhBaoCamThi(dsSV, dsDD, dsLop, maLop);
                break;
            }
        }
    } while (chon != 0);
}

void menuTimKiem(Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD) {
    int chon;
    do {
        inTieuDe("4. TIM KIEM");
        printf("    1. Tim diem danh theo ngay cua lop\n");
        printf("    2. Tim lich su diem danh theo MSSV\n");
        printf("    0. Quay lai menu chinh\n");
        inSeparator();
        chon = Validation::nhapSoNguyen("  Chon", 0, 2);
        switch (chon) {
            case 1: {
                String maLop, ngay;
                Validation::nhapChuoi("  Ma lop", maLop);
                do {
                    Validation::nhapChuoi("  Ngay (DD/MM/YYYY)", ngay);
                } while (!Validation::isValidDate(ngay));
                Vector<PhieuDiemDanh> result;
                Search::timDiemDanhTheoNgayVaLop(dsDD, ngay, maLop, result);
                printf("\n  Ket qua — %d phieu:\n", (int)result.size());
                printf("  %-12s %-30s %s\n", "MSSV", "Ho Ten", "Trang thai");
                inSeparator();
                for (int i = 0; i < (int)result.size(); ++i) {
                    int idx = Search::timSinhVienTheoMSSV(dsSV, result[i].mssv);
                    const char* ten = (idx >= 0) ? dsSV[idx].hoTen.c_str() : "?";
                    const char* ttStr =
                        result[i].trangThai == 'C' ? "Co mat" :
                        result[i].trangThai == 'P' ? "Vang co phep" : "Vang khong phep";
                    printf("  %-12s %-30s %s\n",
                           result[i].mssv.c_str(), ten, ttStr);
                }
                break;
            }
            case 2: {
                String mssv;
                Validation::nhapChuoi("  MSSV", mssv);
                Vector<PhieuDiemDanh> result;
                Search::timDiemDanhTheoMSSV(dsDD, mssv, result);
                int idx = Search::timSinhVienTheoMSSV(dsSV, mssv);
                if (idx >= 0)
                    printf("\n  Lich su diem danh cua: %s (%s)\n",
                           dsSV[idx].hoTen.c_str(), mssv.c_str());
                printf("  %-12s %-12s %-20s\n", "Ngay", "Lop", "Trang thai");
                inSeparator();
                for (int i = 0; i < (int)result.size(); ++i) {
                    const char* ttStr =
                        result[i].trangThai == 'C' ? "Co mat" :
                        result[i].trangThai == 'P' ? "Vang co phep" : "Vang khong phep";
                    printf("  %-12s %-12s %-20s\n",
                           result[i].ngay.c_str(), result[i].maLop.c_str(), ttStr);
                }
                if (result.size() == 0) printf("  Khong co du lieu.\n");
                break;
            }
        }
    } while (chon != 0);
}

void menuBaoCao(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD) {
    int chon;
    do {
        inTieuDe("5. BAO CAO & THONG KE");
        printf("    1. Thong ke si so theo tung buoi hoc\n");
        printf("    2. Danh sach SV vang nhieu nhat\n");
        printf("    3. Xem ti le vang toan lop\n");
        printf("    4. Xuat bao cao ra file .txt\n");
        printf("    0. Quay lai menu chinh\n");
        inSeparator();
        chon = Validation::nhapSoNguyen("  Chon", 0, 4);
        String maLop;
        if (chon >= 1 && chon <= 4) {
            Validation::nhapChuoi("  Ma lop", maLop);
        }
        switch (chon) {
            case 1: BaoCao::thongKeSiSoTheoBuoi(dsDD, maLop); break;
            case 2: {
                int n = Validation::nhapSoNguyen("  Top N sinh vien", 1, 100);
                BaoCao::danhSachVangNhieu(dsSV, dsDD, dsLop, maLop, n);
                break;
            }
            case 3: BaoCao::xemTiLeVangToanLop(dsSV, dsDD, dsLop, maLop); break;
            case 4: BaoCao::xuatBaoCaoFile(dsSV, dsDD, dsLop, maLop); break;
        }
    } while (chon != 0);
}

void hienThiMenuChinh() {
    inTieuDe("HE THONG QUAN LY DIEM DANH LOP HOC");
    printf("    1. Quan ly Lop hoc\n");
    printf("    2. Quan ly Sinh vien\n");
    printf("    3. Diem danh\n");
    printf("    4. Tim kiem\n");
    printf("    5. Bao cao & Thong ke\n");
    printf("    0. Thoat chuong trinh\n");
    inSeparator();
}
