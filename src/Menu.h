#pragma once
#include "Vector.h"
#include "Models.h"
#include "FileIO.h"
#include "Search.h"
#include "Validation.h"
#include "DiemDanhManager.h"
#include "BaoCao.h"

static const char* PATH_LOPHOC    = "data/lophoc.txt";
static const char* PATH_SINHVIEN  = "data/sinhvien.txt";
static const char* PATH_DIEMDANH = "data/diemdanh.txt";

void printHeader(const char* title);
void printSeparator();

// ============================================================
//  1. QUẢN LÝ LỚP HỌC
// ============================================================
void hienThiDanhSachLop(const Vector<LopHoc>& dsLop);
void themLopHoc(Vector<LopHoc>& dsLop);
void suaLopHoc(Vector<LopHoc>& dsLop);
void xoaLopHoc(Vector<LopHoc>& dsLop);
void menuQuanLyLopHoc(Vector<LopHoc>& dsLop);

// ============================================================
//  2. QUẢN LÝ SINH VIÊN
// ============================================================
void hienThiSVTheoLop(const Vector<SinhVien>& dsSV, const String& maLop);
void themSinhVien(Vector<SinhVien>& dsSV, Vector<LopHoc>& dsLop);
void suaSinhVien(Vector<SinhVien>& dsSV);
void xoaSinhVien(Vector<SinhVien>& dsSV);
void menuQuanLySinhVien(Vector<SinhVien>& dsSV, Vector<LopHoc>& dsLop);

// ============================================================
//  3. ĐIỂM DANH
// ============================================================
void menuDiemDanh(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD);

// ============================================================
//  4. TÌM KIẾM
// ============================================================
void menuTimKiem(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD);

// ============================================================
//  5. BÁO CÁO & THỐNG KÊ
// ============================================================
void menuBaoCao(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD);

// ============================================================
//  MENU CHÍNH
// ============================================================
void hienThiMenuChinh();
