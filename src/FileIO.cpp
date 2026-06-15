#include "FileIO.h"
#include <fstream>
#include <cstdlib>

// ============================================================
//  FileIO.cpp — Đọc / ghi file text
//  Dùng std::ifstream / std::ofstream thay fopen/fclose
// ============================================================

namespace FileIO {

// ── Hàm tiện ích: tách chuỗi theo ký tự phân cách ───────────
int splitLine(const char* src, char delim,
              char parts[][256], int maxParts) {
    int count = 0;
    int j = 0;
    for (int i = 0; src[i] != '\0' && src[i] != '\n' && src[i] != '\r'; ++i) {
        if (src[i] == delim) {
            parts[count][j] = '\0';
            ++count;
            j = 0;
            if (count >= maxParts - 1) {
                // Gom toàn bộ phần còn lại vào slot cuối
                ++i;
                int k = 0;
                while (src[i] != '\0' && src[i] != '\n' && src[i] != '\r')
                    parts[count][k++] = src[i++];
                parts[count][k] = '\0';
                return count + 1;
            }
        } else {
            parts[count][j++] = src[i];
        }
    }
    parts[count][j] = '\0';
    return count + 1;
}

// ─────────────────────────────────────────────────────────────
//  ĐỌC FILE — dùng std::ifstream
// ─────────────────────────────────────────────────────────────

bool loadLopHoc(const char* path, Vector<LopHoc>& arr) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return false;
    char line[512];
    while (ifs.getline(line, sizeof(line))) {
        if (line[0] == '\0') continue;
        char p[8][256];
        int n = splitLine(line, '|', p, 8);
        if (n < 8) continue;
        LopHoc lh;
        lh.maLop       = String(p[0]);
        lh.tenLop      = String(p[1]);
        lh.giangVien   = String(p[2]);
        lh.tkb.thu         = atoi(p[3]);
        lh.tkb.tietBatDau  = atoi(p[4]);
        lh.tkb.soTiet      = atoi(p[5]);
        lh.tkb.phong       = String(p[6]);
        lh.tongSoBuoi      = atoi(p[7]);
        arr.push_back(lh);
    }
    return true;
}

bool loadSinhVien(const char* path, Vector<SinhVien>& arr) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return false;
    char line[512];
    while (ifs.getline(line, sizeof(line))) {
        if (line[0] == '\0') continue;
        char p[3][256];
        int n = splitLine(line, '|', p, 3);
        if (n < 3) continue;
        SinhVien sv;
        sv.mssv  = String(p[0]);
        sv.hoTen = String(p[1]);
        sv.maLop = String(p[2]);
        arr.push_back(sv);
    }
    return true;
}

bool loadDiemDanh(const char* path, Vector<PhieuDiemDanh>& arr) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return false;
    char line[512];
    while (ifs.getline(line, sizeof(line))) {
        if (line[0] == '\0') continue;
        char p[4][256];
        int n = splitLine(line, '|', p, 4);
        if (n < 4) continue;
        PhieuDiemDanh dd;
        dd.mssv       = String(p[0]);
        dd.maLop      = String(p[1]);
        dd.ngay       = String(p[2]);
        dd.trangThai  = p[3][0];
        arr.push_back(dd);
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
//  GHI FILE — dùng std::ofstream
// ─────────────────────────────────────────────────────────────

bool saveLopHoc(const char* path, Vector<LopHoc>& arr) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) return false;
    for (int i = 0; i < (int)arr.size(); ++i) {
        LopHoc& lh = arr[i];
        ofs << lh.maLop << '|' << lh.tenLop << '|' << lh.giangVien << '|'
            << lh.tkb.thu << '|' << lh.tkb.tietBatDau << '|'
            << lh.tkb.soTiet << '|' << lh.tkb.phong << '|'
            << lh.tongSoBuoi << '\n';
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
        ofs << dd.mssv << '|' << dd.maLop << '|'
            << dd.ngay << '|' << dd.trangThai << '\n';
    }
    return true;
}

bool appendDiemDanh(const char* path, const PhieuDiemDanh& dd) {
    std::ofstream ofs(path, std::ios::app);
    if (!ofs.is_open()) return false;
    ofs << dd.mssv << '|' << dd.maLop << '|'
        << dd.ngay << '|' << dd.trangThai << '\n';
    return true;
}

} // namespace FileIO
