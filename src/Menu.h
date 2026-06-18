#pragma once
#include "BaoCao.h"
#include "DiemDanhManager.h"
#include "FileIO.h"
#include "Models.h"
#include "Search.h"
#include "Validation.h"
#include "Vector.h"

void printHeader(const char* title);
void printSeparator();

//  1. Quan ly lop hoc
void hienThiDanhSachLop(const Vector<LopHoc>& dsLop);
void themLopHoc(Vector<LopHoc>& dsLop, const char* pathLop);
void suaLopHoc(Vector<LopHoc>& dsLop, const char* pathLop);
void xoaLopHoc(Vector<LopHoc>& dsLop, const char* pathLop);
void menuQuanLyLopHoc(Vector<LopHoc>& dsLop, const char* pathLop);

//  2. Quan ly sinh vien
void hienThiSVTheoLop(const Vector<SinhVien>& dsSV, const String& maLop);
void themSinhVien(Vector<SinhVien>& dsSV, Vector<LopHoc>& dsLop, const char* pathSV);
void suaSinhVien(Vector<SinhVien>& dsSV, const char* pathSV);
void xoaSinhVien(Vector<SinhVien>& dsSV, const char* pathSV);
void menuQuanLySinhVien(Vector<SinhVien>& dsSV, 
                        Vector<LopHoc>& dsLop, 
                        const char* pathSV);

//  3. Diem danh
void menuDiemDanh(Vector<LopHoc>& dsLop, 
                  Vector<SinhVien>& dsSV,
                  Vector<PhieuDiemDanh>& dsDD,
                  const char* pathDD);

//  4. Tim kiem
void menuTimKiem(Vector<LopHoc>& dsLop, 
                 Vector<SinhVien>& dsSV,
                 Vector<PhieuDiemDanh>& dsDD);

//  5. Bao cao & thong ke
void menuBaoCao(Vector<LopHoc>& dsLop, 
                Vector<SinhVien>& dsSV,
                Vector<PhieuDiemDanh>& dsDD,
                const char* exportDir);

//  6. Sap xep
void menuSapXep(Vector<LopHoc>& dsLop, 
                Vector<SinhVien>& dsSV,
                Vector<PhieuDiemDanh>& dsDD,
                const char* pathLop,
                const char* pathSV,
                const char* pathDD);

//  Menu chinh
void hienThiMenuChinh();
