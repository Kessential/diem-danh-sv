#pragma once
#include "Vector.h"
#include "Models.h"

// DiemDanhManager.h - Khai bao logic nghiep vu diem danh

namespace DiemDanhManager {

// Tinh ty le vang cho 1 sinh vien
ThongKeSinhVien tinhTiLeVang(Vector<PhieuDiemDanh>& dsDD,
                             SinhVien& sv, 
                             int tongSoBuoi);

// Ghi diem danh mot buoi cho toan lop
void ghiDiemDanhMoiLop(Vector<SinhVien>& dsSV,
                       Vector<PhieuDiemDanh>& dsDD,
                       const String& maLop, 
                       const String& ngay);

// Quet toan lop, in SV co ty le vang > 20%
void kiemTraCanhBaoCamThi(Vector<SinhVien>& dsSV,
                          Vector<PhieuDiemDanh>& dsDD,
                          Vector<LopHoc>& dsLop,
                          const String& maLop);

// Sua trang thai 1 phieu diem danh (tra ve true neu tim thay)
bool suaDiemDanh(Vector<PhieuDiemDanh>& dsDD,
                 const String& mssv, 
                 const String& maLop,
                 const String& ngay, 
                 TrangThaiDD trangThaiMoi);

}  // namespace DiemDanhManager