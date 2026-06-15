#include "Search.h"

namespace Search {

int timLopHocTheoMa(const Vector<LopHoc>& arr, const String& maLop) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i].maLop.equalsIgnoreCase(maLop)) return (int)i;
    }
    return -1;
}

int timSinhVienTheoMSSV(const Vector<SinhVien>& arr, const String& mssv) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i].mssv.equalsIgnoreCase(mssv)) return (int)i;
    }
    return -1;
}

void timSinhVienTheoLop(const Vector<SinhVien>& dsSV, const String& maLop,
                         Vector<SinhVien>& result) {
    result.clear();
    for (size_t i = 0; i < dsSV.size(); ++i) {
        if (dsSV[i].maLop.equalsIgnoreCase(maLop)) result.push_back(dsSV[i]);
    }
}

void timDiemDanhTheoNgayVaLop(const Vector<PhieuDiemDanh>& dsDD,
                               const String& ngay, const String& maLop,
                               Vector<PhieuDiemDanh>& result) {
    result.clear();
    for (size_t i = 0; i < dsDD.size(); ++i) {
        if (dsDD[i].ngay == ngay && dsDD[i].maLop.equalsIgnoreCase(maLop))
            result.push_back(dsDD[i]);
    }
}

void timDiemDanhTheoMSSV(const Vector<PhieuDiemDanh>& dsDD, const String& mssv,
                          Vector<PhieuDiemDanh>& result) {
    result.clear();
    for (size_t i = 0; i < dsDD.size(); ++i) {
        if (dsDD[i].mssv.equalsIgnoreCase(mssv)) result.push_back(dsDD[i]);
    }
}

void timDiemDanhTheoMSSVvaLop(const Vector<PhieuDiemDanh>& dsDD,
                               const String& mssv, const String& maLop,
                               Vector<PhieuDiemDanh>& result) {
    result.clear();
    for (size_t i = 0; i < dsDD.size(); ++i) {
        if (dsDD[i].mssv.equalsIgnoreCase(mssv) && dsDD[i].maLop.equalsIgnoreCase(maLop))
            result.push_back(dsDD[i]);
    }
}

bool daDiemDanhBuoi(const Vector<PhieuDiemDanh>& dsDD,
                     const String& ngay, const String& maLop) {
    for (size_t i = 0; i < dsDD.size(); ++i) {
        if (dsDD[i].ngay == ngay && dsDD[i].maLop.equalsIgnoreCase(maLop)) return true;
    }
    return false;
}

}
