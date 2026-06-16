#pragma once
#include "Models.h"
#include "Vector.h"

namespace Search {

int timLopHocTheoMa(const Vector<LopHoc> &arr, const String &maLop);
int timSinhVienTheoMSSV(const Vector<SinhVien> &arr, const String &mssv);

void timSinhVienTheoLop(const Vector<SinhVien> &dsSV, const String &maLop,
                        Vector<SinhVien> &result);

void timDiemDanhTheoNgayVaLop(const Vector<PhieuDiemDanh> &dsDD,
                              const String &ngay, const String &maLop,
                              Vector<PhieuDiemDanh> &result);

void timDiemDanhTheoMSSV(const Vector<PhieuDiemDanh> &dsDD, const String &mssv,
                         Vector<PhieuDiemDanh> &result);

void timDiemDanhTheoMSSVvaLop(const Vector<PhieuDiemDanh> &dsDD,
                              const String &mssv, const String &maLop,
                              Vector<PhieuDiemDanh> &result);

bool daDiemDanhBuoi(const Vector<PhieuDiemDanh> &dsDD, const String &ngay,
                    const String &maLop);

}
