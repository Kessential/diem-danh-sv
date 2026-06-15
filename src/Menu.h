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

void inTieuDe(const char* title);
void inSeparator();
// ============================================================
//  1. QUẢN LÝ LỚP HỌC
// ============================================================
void hienThiDanhSachLop(Vector<LopHoc>& dsLop);
void themLopHoc(Vector<LopHoc>& dsLop);
void suaLopHoc(Vector<LopHoc>& dsLop);
void xoaLopHoc(Vector<LopHoc>& dsLop);
void menuQuanLyLopHoc(Vector<LopHoc>& dsLop);

// ============================================================
//  2. QUẢN LÝ SINH VIÊN
// ============================================================
void hienThiSVTheoLop(Vector<SinhVien>& dsSV, const String& maLop);
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
void menuTimKiem(Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD);

// ============================================================
//  5. BÁO CÁO & THỐNG KÊ
// ============================================================
void menuBaoCao(Vector<LopHoc>& dsLop, Vector<SinhVien>& dsSV, Vector<PhieuDiemDanh>& dsDD);

// ============================================================
//  MENU CHÍNH
// ============================================================
void hienThiMenuChinh();
