#include "Search.h"

namespace Search {

// Duyet mang, tra ve index neu maLop khop
int timLopHocTheoMa(const Vector<LopHoc>& arr, const String& maLop) {
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i].maLop.equalsIgnoreCase(maLop)) return (int)i;
  }
  return -1;
}

// Duyet mang, tra ve index neu mssv khop
int timSinhVienTheoMSSV(const Vector<SinhVien>& arr, const String& mssv) {
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i].mssv.equalsIgnoreCase(mssv)) return (int)i;
  }
  return -1;
}

// Loc SV theo maLop, day vao result
void timSinhVienTheoLop(const Vector<SinhVien>& dsSV, 
                        const String& maLop,
                        Vector<SinhVien>& result) {
  result.clear();
  for (size_t i = 0; i < dsSV.size(); ++i) {
    if (dsSV[i].maLop.equalsIgnoreCase(maLop)) result.push_back(dsSV[i]);
  }
}

// Loc phieu diem danh theo ngay va maLop, day vao result
void timDiemDanhTheoNgayVaLop(const Vector<PhieuDiemDanh>& dsDD,
                              const String& ngay, 
                              const String& maLop,
                              Vector<PhieuDiemDanh>& result) {
  result.clear();
  for (size_t i = 0; i < dsDD.size(); ++i) {
    if (dsDD[i].ngay == ngay && dsDD[i].maLop.equalsIgnoreCase(maLop))
      result.push_back(dsDD[i]);
  }
}

// Loc phieu diem danh theo mssv, day vao result
void timDiemDanhTheoMSSV(const Vector<PhieuDiemDanh>& dsDD, 
                         const String& mssv,
                         Vector<PhieuDiemDanh>& result) {
  result.clear();
  for (size_t i = 0; i < dsDD.size(); ++i) {
    if (dsDD[i].mssv.equalsIgnoreCase(mssv)) result.push_back(dsDD[i]);
  }
}

// Loc phieu diem danh theo mssv va maLop, day vao result
void timDiemDanhTheoMSSVvaLop(const Vector<PhieuDiemDanh>& dsDD,
                              const String& mssv,
                              const String& maLop,
                              Vector<PhieuDiemDanh>& result) {
  result.clear();
  for (size_t i = 0; i < dsDD.size(); ++i) {
    if (dsDD[i].mssv.equalsIgnoreCase(mssv) &&
        dsDD[i].maLop.equalsIgnoreCase(maLop))
      result.push_back(dsDD[i]);
  }
}

// Kiem tra ton tai phieu diem danh theo ngay va maLop
bool daDiemDanhBuoi(const Vector<PhieuDiemDanh>& dsDD, 
                    const String& ngay,
                    const String& maLop) {
  for (size_t i = 0; i < dsDD.size(); ++i) {
    if (dsDD[i].ngay == ngay && dsDD[i].maLop.equalsIgnoreCase(maLop))
      return true;
  }
  return false;
}

// Loc toan bo phieu diem danh theo maLop, day vao result
void timDiemDanhTheoLop(const Vector<PhieuDiemDanh>& dsDD,
                        const String& maLop,
                        Vector<PhieuDiemDanh>& result) {
  result.clear();
  for (size_t i = 0; i < dsDD.size(); ++i) {
    if (dsDD[i].maLop.equalsIgnoreCase(maLop))
      result.push_back(dsDD[i]);
  }
}

}  // namespace Search
