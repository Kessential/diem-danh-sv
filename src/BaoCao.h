#pragma once
#include "DiemDanhManager.h"
#include "Models.h"
#include "Sort.h"
#include "Vector.h"

namespace BaoCao {

// Comparator sap xep ThongKeSinhVien theo soVang giam dan
struct SoVangDesc {
  bool operator()(const ThongKeSinhVien& a, const ThongKeSinhVien& b) const {
    return a.soVang > b.soVang;
  }
};

// Xay dung mang ThongKe cho toan lop
void xayDungThongKe(Vector<SinhVien>& dsSV, 
                    Vector<PhieuDiemDanh>& dsDD,
                    Vector<LopHoc>& dsLop, 
                    const String& maLop,
                    Vector<ThongKeSinhVien>& result);

// Thong ke si so theo tung buoi hoc
void thongKeSiSoTheoBuoi(Vector<PhieuDiemDanh>& dsDD, const String& maLop);

// Top N sinh vien vang nhieu nhat
void danhSachVangNhieu(Vector<SinhVien>& dsSV,
                       Vector<PhieuDiemDanh>& dsDD,
                       Vector<LopHoc>& dsLop, 
                       const String& maLop, 
                       int topN);

// Xem ty le vang toan lop
void xemTiLeVangToanLop(Vector<SinhVien>& dsSV, 
                        Vector<PhieuDiemDanh>& dsDD,
                        Vector<LopHoc>& dsLop, 
                        const String& maLop);

// Xuat bao cao ra file text
// Ten file: baocao_<maLop>.txt
void xuatBaoCaoFile(Vector<SinhVien>& dsSV, 
                    Vector<PhieuDiemDanh>& dsDD,
                    Vector<LopHoc>& dsLop, 
                    const String& maLop);

}  // namespace BaoCao