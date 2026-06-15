#pragma once
#include "Vector.h"
#include "Sort.h"
#include "Models.h"
#include "DiemDanhManager.h"

// ============================================================
//  BaoCao.h — Thống kê & báo cáo
// ============================================================

namespace BaoCao {

// ── Comparator để sắp xếp ThongKeSinhVien theo soVang giảm dần
struct SoVangDesc {
    bool operator()(const ThongKeSinhVien& a, const ThongKeSinhVien& b) const {
        return a.soVang > b.soVang; // Giảm dần
    }
};

// ── Xây dựng mảng ThongKe cho toàn lớp ──────────────────────
void xayDungThongKe(Vector<SinhVien>& dsSV,
                             Vector<PhieuDiemDanh>& dsDD,
                             Vector<LopHoc>& dsLop,
                             const String& maLop,
                             Vector<ThongKeSinhVien>& result);

// ── Thống kê sĩ số theo từng buổi học ────────────────────────
// In bảng: Ngày | Có mặt | Vắng phép | Vắng K.phép | Tổng vắng
void thongKeSiSoTheoBuoi(Vector<PhieuDiemDanh>& dsDD,
                                  const String& maLop);

// ── Top N sinh viên vắng nhiều nhất ──────────────────────────
void danhSachVangNhieu(Vector<SinhVien>& dsSV,
                               Vector<PhieuDiemDanh>& dsDD,
                               Vector<LopHoc>& dsLop,
                               const String& maLop,
                               int topN);

// ── Xem tỷ lệ vắng toàn lớp ──────────────────────────────────
void xemTiLeVangToanLop(Vector<SinhVien>& dsSV,
                                 Vector<PhieuDiemDanh>& dsDD,
                                 Vector<LopHoc>& dsLop,
                                 const String& maLop);

// ── Xuất báo cáo ra file text ─────────────────────────────────
// Tên file: baocao_<maLop>.txt
void xuatBaoCaoFile(Vector<SinhVien>& dsSV,
                             Vector<PhieuDiemDanh>& dsDD,
                             Vector<LopHoc>& dsLop,
                             const String& maLop);

} // namespace BaoCao
