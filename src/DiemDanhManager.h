#pragma once
#include "Vector.h"
#include "Models.h"

// ============================================================
//  DiemDanhManager.h — Khai báo logic nghiệp vụ điểm danh
// ============================================================

namespace DiemDanhManager {

// Tính tỷ lệ vắng cho 1 sinh viên
ThongKeSinhVien tinhTiLeVang(Vector<PhieuDiemDanh>& dsDD,
                              SinhVien& sv, int tongSoBuoi);

// Ghi điểm danh một buổi cho toàn lớp
void ghiDiemDanhMoiLop(Vector<SinhVien>& dsSV,
                        Vector<PhieuDiemDanh>& dsDD,
                        const String& maLop, const String& ngay);

// Quét toàn lớp, in SV có tỷ lệ vắng > 20%
void kiemTraCanhBaoCamThi(Vector<SinhVien>& dsSV,
                           Vector<PhieuDiemDanh>& dsDD,
                           Vector<LopHoc>& dsLop,
                           const String& maLop);

// Sửa trạng thái 1 phiếu điểm danh (trả về true nếu tìm thấy)
bool suaDiemDanh(Vector<PhieuDiemDanh>& dsDD,
                  const String& mssv, const String& maLop,
                  const String& ngay, char trangThaiMoi);

} // namespace DiemDanhManager
