#include "FileIO.h"

#include <fstream>
#include <iostream>

namespace FileIO {

// ── Hàm tiện ích: tách chuỗi theo ký tự phân cách ───────────
void splitLine(const String& src, char delim, Vector<String>& parts) {
  size_t capacity = 64;
  char* buf = new char[capacity];
  size_t k = 0;

  for (size_t i = 0; i < src.length(); ++i) {
    if (src[i] == delim) {
      buf[k] = '\0';
      parts.push_back(String(buf));
      k = 0;
    } else {
      if (k + 1 >= capacity) {
        capacity *= 2;
        char* newBuf = new char[capacity];
        for (size_t j = 0; j < k; ++j) newBuf[j] = buf[j];
        delete[] buf;
        buf = newBuf;
      }
      buf[k++] = src[i];
    }
  }
  buf[k] = '\0';
  parts.push_back(String(buf));
  delete[] buf;
}

// ─────────────────────────────────────────────────────────────
//   LOAD DỮ LIỆU TỪ FILE TXT
// ─────────────────────────────────────────────────────────────

bool loadLopHoc(const char* path, Vector<LopHoc>& arr) {
  std::ifstream ifs(path);
  if (!ifs.is_open()) return false;
  String line;
  while (true) {
    getline(ifs, line);
    if (line.empty() && (ifs.eof() || ifs.fail())) break;
    if (line.empty()) continue;

    Vector<String> p;
    splitLine(line, '|', p);
    if (p.size() < 8) continue;

    LopHoc lh;
    lh.maLop = p[0];
    lh.tenLop = p[1];
    lh.giangVien = p[2];
    lh.tkb.thu = p[3].toInt();
    lh.tkb.tietBatDau = p[4].toInt();
    lh.tkb.soTiet = p[5].toInt();
    lh.tkb.phong = p[6];
    lh.tongSoBuoi = p[7].toInt();
    arr.push_back(lh);
  }
  return true;
}

bool loadSinhVien(const char *path, Vector<SinhVien> &arr) {
  std::ifstream ifs(path);
  if (!ifs.is_open())
    return false;
  String line;
  while (true) {
    getline(ifs, line);
    if (line.empty() && (ifs.eof() || ifs.fail()))
      break;
    if (line.empty())
      continue;

    Vector<String> p;
    splitLine(line, '|', p);
    if (p.size() < 3)
      continue;

    SinhVien sv;
    sv.mssv  = p[0];
    sv.hoTen = p[1];
    sv.maLop = p[2];
    arr.push_back(sv);
  }
  return true;
}

bool loadDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr) {
  std::ifstream ifs(path);
  if (!ifs.is_open()) return false;
  String line;
  while (true) {
    getline(ifs, line);
    if (line.empty() && (ifs.eof() || ifs.fail())) break;
    if (line.empty()) continue;

    Vector<String> p;
    splitLine(line, '|', p);
    if (p.size() < 4) continue;

    PhieuDiemDanh dd;
    dd.mssv = p[0];
    dd.maLop = p[1];
    dd.ngay = p[2];
    dd.trangThai = static_cast<TrangThaiDD>(p[3][0]);
    arr.push_back(dd);
  }
  return true;
}

// ─────────────────────────────────────────────────────────────
//   SAVE / APPEND DỮ LIỆU XUỐNG FILE TXT
// ─────────────────────────────────────────────────────────────

bool saveLopHoc(const char* path, Vector<LopHoc>& arr) {
  std::ofstream ofs(path);
  if (!ofs.is_open()) return false;
  for (int i = 0; i < (int)arr.size(); ++i) {
    LopHoc& lh = arr[i];
    ofs << lh.maLop << '|' << lh.tenLop << '|' << lh.giangVien << '|'
        << lh.tkb.thu << '|' << lh.tkb.tietBatDau << '|' << lh.tkb.soTiet << '|'
        << lh.tkb.phong << '|' << lh.tongSoBuoi << '\n';
  }
  return true;
}

bool saveSinhVien(const char* path, Vector<SinhVien>& arr) {
  std::ofstream ofs(path);
  if (!ofs.is_open()) return false;
  for (int i = 0; i < (int)arr.size(); ++i) {
    SinhVien& sv = arr[i];
    ofs << sv.mssv << '|' << sv.hoTen << '|' << sv.maLop << '\n';
  }
  return true;
}

bool saveDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr) {
  std::ofstream ofs(path);
  if (!ofs.is_open()) return false;
  for (int i = 0; i < (int)arr.size(); ++i) {
    PhieuDiemDanh& dd = arr[i];
    ofs << dd.mssv << '|' << dd.maLop << '|' << dd.ngay << '|'
        << static_cast<char>(dd.trangThai) << '\n';
  }
  return true;
}

bool appendDiemDanh(const char* path, const PhieuDiemDanh& dd) {
  std::ofstream ofs(path, std::ios::app);
  if (!ofs.is_open()) return false;
  ofs << dd.mssv << '|' << dd.maLop << '|' << dd.ngay << '|'
      << static_cast<char>(dd.trangThai) << '\n';
  return true;
}

}  // namespace FileIO
