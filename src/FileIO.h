#pragma once
#include "Vector.h"
#include "Models.h"

namespace FileIO {

// Tach chuoi theo ky tu phan cach - tu viet bang vong lap ky tu
void splitLine(const String& src, char delim, Vector<String>& parts);

// Doc file
bool loadLopHoc(const char* path, Vector<LopHoc>& arr);
bool loadSinhVien(const char* path, Vector<SinhVien>& arr);
bool loadDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr);

// Ghi file (ghi de toan bo)
bool saveLopHoc(const char* path, Vector<LopHoc>& arr);
bool saveSinhVien(const char* path, Vector<SinhVien>& arr);
bool saveDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr);

// Append 1 phieu moi - nhanh hon rewrite toan bo
bool appendDiemDanh(const char* path, const PhieuDiemDanh& dd);

} // namespace FileIO
