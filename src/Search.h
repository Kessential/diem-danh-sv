#pragma once
#include "Models.h"
#include "Vector.h"

namespace Search {

// --- Tim kiem vi tri (tra ve index, -1 neu khong tim thay) ---

// Tim lop hoc theo ma lop
int timLopHocTheoMa(const Vector<LopHoc>& arr, const String& maLop);

// Tim sinh vien theo MSSV
int timSinhVienTheoMSSV(const Vector<SinhVien>& arr, const String& mssv);

// --- Tim kiem danh sach (luu ket qua vao vector result) ---

// Tim sinh vien thuoc 1 lop
void timSinhVienTheoLop(const Vector<SinhVien>& dsSV,
                        const String& maLop,
                        Vector<SinhVien>& result);

// Tim phieu diem danh theo ngay va lop
void timDiemDanhTheoNgayVaLop(const Vector<PhieuDiemDanh>& dsDD,
                              const String& ngay, 
                              const String& maLop,
                              Vector<PhieuDiemDanh>& result);

// Tim phieu diem danh theo MSSV
void timDiemDanhTheoMSSV(const Vector<PhieuDiemDanh>& dsDD, 
                        const String& mssv,
                        Vector<PhieuDiemDanh>& result);

// Tim phieu diem danh theo MSSV va lop
void timDiemDanhTheoMSSVvaLop(const Vector<PhieuDiemDanh>& dsDD,
                              const String& mssv, 
                              const String& maLop,
                              Vector<PhieuDiemDanh>& result);

// --- Kiem tra ton tai ---

// Kiem tra lop da diem danh trong ngay chua
bool daDiemDanhBuoi(const Vector<PhieuDiemDanh>& dsDD, 
                    const String& ngay,
                    const String& maLop);

}  // namespace Search
