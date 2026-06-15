#pragma once
#include "Vector.h"
#include "Models.h"

// ============================================================
//  FileIO.h — Khai báo đọc / ghi file text
// ============================================================

namespace FileIO {

// Tách chuỗi theo ký tự phân cách — tự viết bằng vòng lặp ký tự
int splitLine(const char* src, char delim, char parts[][256], int maxParts);

// Đọc file
bool loadLopHoc(const char* path, Vector<LopHoc>& arr);
bool loadSinhVien(const char* path, Vector<SinhVien>& arr);
bool loadDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr);

// Ghi file (ghi đè toàn bộ)
bool saveLopHoc(const char* path, Vector<LopHoc>& arr);
bool saveSinhVien(const char* path, Vector<SinhVien>& arr);
bool saveDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr);

// Append 1 phiếu mới — nhanh hơn rewrite toàn bộ
bool appendDiemDanh(const char* path, const PhieuDiemDanh& dd);

} // namespace FileIO
