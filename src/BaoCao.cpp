#include "BaoCao.h"
#include <fstream>
#include <cstdio>

namespace BaoCao {

void xayDungThongKe(Vector<SinhVien>& dsSV,
                             Vector<PhieuDiemDanh>& dsDD,
                             Vector<LopHoc>& dsLop,
                             const String& maLop,
                             Vector<ThongKeSinhVien>& result) {
    result.clear();
    int tongSoBuoi = 0;
    for (int i = 0; i < (int)dsLop.size(); ++i) {
        if (dsLop[i].maLop == maLop) {
            tongSoBuoi = dsLop[i].tongSoBuoi;
            break;
        }
    }
    for (int i = 0; i < (int)dsSV.size(); ++i) {
        if (dsSV[i].maLop == maLop) {
            ThongKeSinhVien tk =
                DiemDanhManager::tinhTiLeVang(dsDD, dsSV[i], tongSoBuoi);
            result.push_back(tk);
        }
    }
}

static Vector<String> collectNgayUnique(Vector<PhieuDiemDanh>& dsDD, const String& maLop) {
    Vector<String> ngayUnique;
    for (int i = 0; i < (int)dsDD.size(); ++i) {
        if (!(dsDD[i].maLop == maLop)) continue;
        bool trung = false;
        for (int j = 0; j < (int)ngayUnique.size(); ++j) {
            if (ngayUnique[j] == dsDD[i].ngay) { trung = true; break; }
        }
        if (!trung) ngayUnique.push_back(dsDD[i].ngay);
    }
    return ngayUnique;
}

void thongKeSiSoTheoBuoi(Vector<PhieuDiemDanh>& dsDD, const String& maLop) {
    Vector<String> ngayUnique = collectNgayUnique(dsDD, maLop);

    printf("\n  === THONG KE SI SO THEO BUOI — Lop %s ===\n\n", maLop.c_str());
    printf("  %-12s %9s %11s %12s %12s\n",
           "Ngay", "Co mat", "Vang phep", "Vang K.phep", "Tong vang");
    printf("  %s\n",
           "--------------------------------------------------------------");

    for (int i = 0; i < (int)ngayUnique.size(); ++i) {
        int coMat = 0, vangP = 0, vangK = 0;
        for (int j = 0; j < (int)dsDD.size(); ++j) {
            if (!(dsDD[j].maLop == maLop)) continue;
            if (!(dsDD[j].ngay == ngayUnique[i])) continue;
            if (dsDD[j].trangThai == 'C') ++coMat;
            else if (dsDD[j].trangThai == 'P') ++vangP;
            else if (dsDD[j].trangThai == 'K') ++vangK;
        }
        printf("  %-12s %9d %11d %12d %12d\n",
               ngayUnique[i].c_str(), coMat, vangP, vangK, vangP + vangK);
    }
    if (ngayUnique.size() == 0) {
        printf("  Chua co du lieu diem danh nao.\n");
    }
}

void danhSachVangNhieu(Vector<SinhVien>& dsSV,
                               Vector<PhieuDiemDanh>& dsDD,
                               Vector<LopHoc>& dsLop,
                               const String& maLop,
                               int topN) {
    Vector<ThongKeSinhVien> dsThongKe;
    xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);

    Sort::sort(dsThongKe, SoVangDesc{});

    int in = (topN > (int)dsThongKe.size()) ? (int)dsThongKe.size() : topN;

    printf("\n  === TOP %d SINH VIEN VANG NHIEU NHAT — Lop %s ===\n\n",
           in, maLop.c_str());
    printf("  %-4s %-12s %-25s %8s %8s %10s\n",
           "STT", "MSSV", "Ho Ten", "SoVang", "TiLe%", "CamThi?");
    printf("  %s\n", "-------------------------------------------------------------------");

    for (int i = 0; i < in; ++i) {
        printf("  %-4d %-12s %-25s %8d %7.1f%% %10s\n",
               i + 1,
               dsThongKe[i].mssv.c_str(),
               dsThongKe[i].hoTen.c_str(),
               dsThongKe[i].soVang,
               dsThongKe[i].tiLe,
               dsThongKe[i].nguyCoiCamThi ? "[CANH BAO]" : "OK");
    }
}

void xemTiLeVangToanLop(Vector<SinhVien>& dsSV,
                                 Vector<PhieuDiemDanh>& dsDD,
                                 Vector<LopHoc>& dsLop,
                                 const String& maLop) {
    Vector<ThongKeSinhVien> dsThongKe;
    xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);

    printf("\n  === TI LE VANG TOAN LOP — Lop %s ===\n\n", maLop.c_str());
    printf("  %-12s %-25s %8s %12s %8s %10s\n",
           "MSSV", "Ho Ten", "SoVang", "VangK.phep", "TiLe%", "CamThi?");
    printf("  %s\n",
           "----------------------------------------------------------------------");

    for (int i = 0; i < (int)dsThongKe.size(); ++i) {
        printf("  %-12s %-25s %8d %12d %7.1f%% %10s\n",
               dsThongKe[i].mssv.c_str(),
               dsThongKe[i].hoTen.c_str(),
               dsThongKe[i].soVang,
               dsThongKe[i].soVangKhongPhep,
               dsThongKe[i].tiLe,
               dsThongKe[i].nguyCoiCamThi ? "[CANH BAO]" : "OK");
    }
}

void xuatBaoCaoFile(Vector<SinhVien>& dsSV,
                             Vector<PhieuDiemDanh>& dsDD,
                             Vector<LopHoc>& dsLop,
                             const String& maLop) {
    char tenFile[128];
    sprintf(tenFile, "data/baocao_%s.txt", maLop.c_str());

    std::ofstream out(tenFile);
    if (!out) {
        printf("  [!] Khong the tao file bao cao: %s\n", tenFile);
        return;
    }

    out << "BAO CAO DIEM DANH — LOP " << maLop.c_str() << "\n";
    out << "=========================================\n\n";

    for (int i = 0; i < (int)dsLop.size(); ++i) {
        if (dsLop[i].maLop == maLop) {
            out << "Mon hoc   : " << dsLop[i].tenLop.c_str() << "\n";
            out << "Giang vien: " << dsLop[i].giangVien.c_str() << "\n";
            out << "Phong     : " << dsLop[i].tkb.phong.c_str() << "  |  Thu " << dsLop[i].tkb.thu 
                << "  |  Tiet " << dsLop[i].tkb.tietBatDau << " - " << (dsLop[i].tkb.tietBatDau + dsLop[i].tkb.soTiet - 1) << "\n";
            out << "Tong so buoi: " << dsLop[i].tongSoBuoi << "\n\n";
            break;
        }
    }

    out << "--- THONG KE SI SO THEO BUOI ---\n";
    char buf[256];
    sprintf(buf, "%-12s %9s %11s %12s %12s", "Ngay", "Co mat", "Vang phep", "Vang K.phep", "Tong vang");
    out << buf << "\n--------------------------------------------------------------\n";

    Vector<String> ngayUnique = collectNgayUnique(dsDD, maLop);
    for (int i = 0; i < (int)ngayUnique.size(); ++i) {
        int coMat = 0, vangP = 0, vangK = 0;
        for (int j = 0; j < (int)dsDD.size(); ++j) {
            if (!(dsDD[j].maLop == maLop) || !(dsDD[j].ngay == ngayUnique[i])) continue;
            if (dsDD[j].trangThai == 'C') ++coMat;
            else if (dsDD[j].trangThai == 'P') ++vangP;
            else if (dsDD[j].trangThai == 'K') ++vangK;
        }
        sprintf(buf, "%-12s %9d %11d %12d %12d",
                ngayUnique[i].c_str(), coMat, vangP, vangK, vangP + vangK);
        out << buf << "\n";
    }

    out << "\n--- TI LE VANG TUNG SINH VIEN ---\n";
    sprintf(buf, "%-12s %-25s %8s %8s %10s",
            "MSSV", "Ho Ten", "SoVang", "TiLe%", "CamThi?");
    out << buf << "\n------------------------------------------------------------\n";

    Vector<ThongKeSinhVien> dsThongKe;
    xayDungThongKe(dsSV, dsDD, dsLop, maLop, dsThongKe);
    Sort::sort(dsThongKe, SoVangDesc{});

    for (int i = 0; i < (int)dsThongKe.size(); ++i) {
        sprintf(buf, "%-12s %-25s %8d %7.1f%% %10s",
                dsThongKe[i].mssv.c_str(),
                dsThongKe[i].hoTen.c_str(),
                dsThongKe[i].soVang,
                dsThongKe[i].tiLe,
                dsThongKe[i].nguyCoiCamThi ? "[CANH BAO]" : "OK");
        out << buf << "\n";
    }

    out.close();
    printf("  [OK] Bao cao da xuat ra: %s\n", tenFile);
}

} // namespace BaoCao
