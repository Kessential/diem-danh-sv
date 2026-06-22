# Hệ Thống Quản Lý Điểm Danh Sinh Viên

> **KTLT_DiemDanh** — Ứng dụng console quản lý điểm danh lớp học, được viết hoàn toàn bằng C++17 thuần (không sử dụng STL containers).

## Mục lục

- [Giới thiệu](#-giới-thiệu)
- [Tính năng](#-tính-năng)
- [Kiến trúc dự án](#-kiến-trúc-dự-án)
- [Cấu trúc dữ liệu](#-cấu-trúc-dữ-liệu)
- [Định dạng file dữ liệu](#-định-dạng-file-dữ-liệu)
- [Yêu cầu hệ thống](#-yêu-cầu-hệ-thống)
- [Hướng dẫn biên dịch](#-hướng-dẫn-biên-dịch)
- [Hướng dẫn sử dụng](#-hướng-dẫn-sử-dụng)
- [Kiểm thử](#-kiểm-thử)
- [Dữ liệu mẫu](#-dữ-liệu-mẫu)
- [Cấu trúc thư mục](#-cấu-trúc-thư-mục)

---

## Giới thiệu

Đây là đồ án môn **Kỹ thuật lập trình (KTLT)** — một hệ thống quản lý điểm danh sinh viên hoạt động trên giao diện console. Chương trình được thiết kế với triết lý **tự cài đặt từ gốc (from scratch)**:

- **Không sử dụng** `std::vector`, `std::string`, `std::sort` hay bất kỳ STL container nào.
- Tự viết class `Vector<T>` (mảng động template) với đầy đủ copy/move semantics.
- Tự viết class `String` (chuỗi ký tự động) thay thế `std::string`.
- Tự viết thuật toán **Hoare QuickSort** (có tối ưu Median-of-Three + Insertion Sort cutoff).
- Dữ liệu được lưu trữ dưới dạng file text (`.txt`), đọc/ghi thông qua module `FileIO`.

---

## Tính năng

### 1. Quản lý Lớp học
| Chức năng | Mô tả |
|---|---|
| Xem danh sách | Hiển thị bảng tất cả lớp học (mã lớp, tên HP, giảng viên, TKB, phòng, số buổi) |
| Thêm lớp | Thêm lớp mới với đầy đủ thông tin, kiểm tra trùng mã lớp |
| Sửa lớp | Sửa từng trường, nhấn Enter để giữ nguyên giá trị hiện tại |
| Xóa lớp | Xóa lớp kèm cascade delete toàn bộ sinh viên và phiếu điểm danh liên quan |

### 2. Quản lý Sinh viên
| Chức năng | Mô tả |
|---|---|
| Xem theo lớp | Hiển thị danh sách sinh viên thuộc 1 lớp |
| Thêm sinh viên | Thêm SV mới, kiểm tra trùng MSSV, kiểm tra mã lớp tồn tại |
| Sửa sinh viên | Sửa họ tên theo MSSV |
| Xóa sinh viên | Xóa SV kèm cascade delete toàn bộ phiếu điểm danh liên quan |

### 3. Điểm danh
| Chức năng | Mô tả |
|---|---|
| Ghi nhận buổi mới | Điểm danh toàn lớp theo ngày, phát hiện buổi đã điểm danh |
| Xem / Sửa | Xem điểm danh theo ngày + lớp, sửa trạng thái từng SV |
| Cảnh báo cấm thi | Quét toàn lớp, cảnh báo SV có tỉ lệ vắng KP ≥ 20% hoặc tổng vắng ≥ 30% |

### 4. Tìm kiếm
- Tìm điểm danh theo **ngày + lớp**
- Tìm lịch sử điểm danh theo **MSSV**
- Xem **các ngày đã điểm danh** của một lớp
- Tìm kiếm **không phân biệt hoa/thường** (case-insensitive)

### 5. Sắp xếp
- Sắp xếp **lớp học** theo mã lớp (tăng/giảm dần)
- Sắp xếp **sinh viên** theo MSSV hoặc theo Mã lớp → Tên → Họ đệm → MSSV (tăng/giảm dần)
- Sắp xếp **điểm danh** theo Mã lớp → Ngày → MSSV (tăng/giảm dần)
- Thuật toán: **Hoare QuickSort** + Median-of-Three + Insertion Sort cutoff (n < 16)

### 6. Báo cáo & Thống kê
| Chức năng | Mô tả |
|---|---|
| Thống kê sĩ số | Sĩ số có mặt / vắng phép / vắng KP theo từng buổi học |
| Top N vắng nhiều | Danh sách SV vắng nhiều nhất (sắp xếp giảm dần) |
| Tỉ lệ vắng toàn lớp | Bảng thống kê chi tiết: số vắng, tỉ lệ KP%, tỉ lệ tổng%, cảnh báo cấm thi |
| Xuất file báo cáo | Xuất báo cáo tổng hợp ra file `export/baocao_<maLop>.txt` |

---

## Kiến trúc dự án

```
┌──────────────────────────────────────────────────────────┐
│                       main.cpp                           │
│               (Khởi tạo & vòng lặp menu)                 │
├──────────────────────────────────────────────────────────┤
│                       Menu.cpp                           │
│         (Giao diện console, điều phối thao tác)          │
├────────────┬────────────┬────────────┬───────────────────┤
│ DiemDanh-  │  BaoCao    │  Search    │    Validation     │
│ Manager    │  (Thống kê │  (Tìm kiếm │    (Kiểm tra      │
│ (Nghiệp vụ │  & báo cáo)│  & lọc)    │    đầu vào)       │
│  điểm danh)│            │            │                   │
├────────────┴────────────┴────────────┴───────────────────┤
│                      FileIO.cpp                          │
│             (Đọc/ghi file text pipe-delimited)           │
├──────────────────────────────────────────────────────────┤
│    Models.h     │    Vector.h     │   CustomString.h     │
│   (Struct dữ    │  (Mảng động     │   (Chuỗi ký tự       │
│    liệu)        │   template)     │    tự viết)          │
├─────────────────┴─────────────────┴──────────────────────┤
│                       Sort.h                             │
│      (Hoare QuickSort template + custom comparator)      │
└──────────────────────────────────────────────────────────┘
```

### Mô tả các module

| Module | File | Mô tả |
|--------|------|-------|
| **CustomString** | `CustomString.h/cpp` | Class `String` tự cài đặt thay thế `std::string`. 1. Tránh lệ thuộc hoàn toàn vào C-string chuẩn qua helper tự viết (`my_strlen`, `my_memcpy`, `my_strcmp`). 2. Xử lý an toàn ngắt dòng/buffer stream khi `getline` với tự động nhân đôi sức chứa. 3. `toInt()` chống tràn (overflow/underflow) an toàn. 4. Ép kiểu `static_cast<String&&>` cho **Move Semantics** tránh việc dùng `std::move`. |
| **Vector** | `Vector.h` | Class template `Vector<T>` thay thế `std::vector`. 1. Triển khai chuẩn **Copy-and-Swap Idiom** an toàn ở toán tử gán. 2. Quản lý bộ nhớ mảng động tối ưu (chiến lược `cap * 2`). 3. Tương thích với cấu trúc Range-based for loop (`for (auto x : vec)`) qua iterator trỏ cấp thấp (raw pointers). 4. Ép kiểu Move thủ công qua `static_cast<T&&>`. |
| **Models** | `Models.h` | Định nghĩa các struct dữ liệu: `LopHoc`, `SinhVien`, `PhieuDiemDanh`, `ThoiKhoaBieu`, `ThongKeSinhVien`, `ThongKeBuoi`. Enum `TrangThaiDD` (C/P/K). |
| **FileIO** | `FileIO.h/cpp` | Đọc/ghi file pipe-delimited (`|`). Cơ chế tách chuỗi cấp phát động an toàn khi nạp dữ liệu. Hỗ trợ append phiếu điểm danh thay vì ghi lại toàn bộ giúp tối ưu I/O. |
| **Search** | `Search.h/cpp` | Thuật toán **Linear Search** để lọc danh sách. Mọi so sánh đối chiếu chuỗi (như mã SV, Mã lớp) đều thiết kế ở dạng **Không phân biệt hoa/thường (case-insensitive)** thông qua `equalsIgnoreCase` để tối ưu trải nghiệm nhập liệu (User Experience). |
| **Sort** | `Sort.h` | Tối ưu hóa **Hoare QuickSort** triệt để: 1. Dùng **Median-of-Three** (chọn phần tử trục là trung vị của low, mid, high) giúp hạn chế O(N²). 2. Dùng đệ quy trên phân đoạn nhỏ trước để tối ưu **Tail Recursion**. 3. Áp dụng **Insertion Sort Cutoff** (< 16 phần tử). 4. Template linh hoạt nhận custom comparator. |
| **Validation** | `Validation.h/cpp` | Tường lửa dữ liệu đầu vào. Xử lý triệt để lỗi luồng nhập (trôi lệnh) qua `cin.clear` & `cin.ignore`. Kiểm tra logic sâu: check năm nhuận 100% hợp lệ cho format DD/MM/YYYY; MSSV chỉ chữ/số. Hỗ trợ UX cập nhật dữ liệu với tính năng **Bảo lưu** (Enter để giữ nguyên). |
| **DiemDanhManager** | `DiemDanhManager.h/cpp` | Nghiệp vụ điểm danh: tính tỉ lệ vắng, ghi điểm danh toàn lớp, kiểm tra cảnh báo cấm thi, sửa phiếu điểm danh. |
| **BaoCao** | `BaoCao.h/cpp` | Thống kê & báo cáo: thống kê sĩ số theo buổi, top N vắng nhiều, tỉ lệ vắng toàn lớp, xuất báo cáo ra file text. |
| **Menu** | `Menu.h/cpp` | Giao diện console: menu chính (6 chức năng + thoát), các sub-menu, hiển thị bảng dữ liệu có căn cột bằng `<iomanip>`, các hàm sắp xếp tương tác. |

---

## Cấu trúc dữ liệu

### Enum trạng thái điểm danh

```cpp
enum class TrangThaiDD : char {
  CO_MAT          = 'C',   // Có mặt
  VANG_PHEP       = 'P',   // Vắng có phép
  VANG_KHONG_PHEP = 'K'    // Vắng không phép
};
```

### Các struct chính

```
LopHoc                          SinhVien
├── maLop    (String)           ├── mssv   (String)
├── tenLop   (String)           ├── hoTen  (String)
├── giangVien (String)          └── maLop  (String)
├── tkb      (ThoiKhoaBieu)
│   ├── thu        (int)        PhieuDiemDanh
│   ├── tietBatDau (int)        ├── mssv      (String)
│   ├── soTiet     (int)        ├── maLop     (String)
│   └── phong      (String)     ├── ngay      (String)
└── tongSoBuoi (int)            └── trangThai (TrangThaiDD)
```

### Quy tắc cảnh báo cấm thi

| Điều kiện | Ngưỡng |
|-----------|--------|
| (A) Vắng không phép | ≥ 20% tổng số buổi |
| (B) Tổng vắng (P + K) | ≥ 30% tổng số buổi |
| Cảnh báo kích hoạt | Khi thỏa (A) **hoặc** (B) |

---

## Định dạng file dữ liệu

Tất cả file sử dụng ký tự `|` (pipe) làm dấu phân cách, mỗi bản ghi trên 1 dòng.

### `data/lophoc.txt`
```
MaLop|TenLop|GiangVien|Thu|TietBatDau|SoTiet|Phong|TongSoBuoi
```
Ví dụ:
```
KTLT_01|Ky thuat lap trinh|Nguyen Van An|3|1|4|B4-201|15
```

### `data/sinhvien.txt`
```
MSSV|HoTen|MaLop
```
Ví dụ:
```
22010001|Mai Xuan Loc|KTLT_01
```

### `data/diemdanh.txt`
```
MSSV|MaLop|Ngay(DD/MM/YYYY)|TrangThai(C/P/K)
```
Ví dụ:
```
22010001|KTLT_01|01/09/2025|C
```

---

## Yêu cầu hệ thống

- **Trình biên dịch C++17**: GCC ≥ 7, Clang ≥ 5, MSVC ≥ 19.14
- **CMake** ≥ 3.10
- **Hệ điều hành**: Windows / Linux / macOS
- Hỗ trợ UTF-8 console trên Windows (tự động thiết lập qua `SetConsoleCP`)

---

## Hướng dẫn biên dịch

### Sử dụng CMake (khuyến nghị)

```bash
# Clone hoặc tải project
cd diem-danh-sv

# Tạo thư mục build
mkdir -p build && cd build

# Cấu hình (Release mode mặc định)
cmake ..

# Biên dịch
cmake --build . --config Release

# Chạy chương trình (quay về thư mục gốc)
cd ..
./build/diemdanh
```

### Trên Windows (MinGW)

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
cd ..
.\build\diemdanh.exe
```

### Trên Windows (Visual Studio)

```bash
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
cd ..
.\build\Release\diemdanh.exe
```

> **Lưu ý**: Chương trình đọc dữ liệu từ đường dẫn tương đối `data/`, vì vậy phải chạy từ **thư mục gốc** của project.

---

## Hướng dẫn sử dụng

### Menu chính

```
  ╔══════════════════════════════════════════════╗
  ║  HE THONG QUAN LY DIEM DANH LOP HOC          ║
  ╚══════════════════════════════════════════════╝
    1. Quan ly Lop hoc
    2. Quan ly Sinh vien
    3. Diem danh
    4. Tim kiem
    5. Sap xep
    6. Bao cao & Thong ke
    0. Thoat chuong trinh
  ────────────────────────────────────────────────
```

### Luồng thao tác điển hình

```
1. Tạo lớp học      →  Menu 1 → Thêm lớp
2. Thêm sinh viên   →  Menu 2 → Thêm SV (chỉ định mã lớp đã tồn tại)
3. Điểm danh        →  Menu 3 → Ghi nhận buổi mới (nhập trạng thái C/P/K)
4. Xem báo cáo      →  Menu 6 → Chọn loại thống kê
5. Xuất file         →  Menu 6 → Xuất báo cáo ra file .txt
```

### Quy ước thông báo console

| Ký hiệu | Ý nghĩa |
|----------|---------|
| `[OK]` | Thao tác thành công |
| `[!]` | Cảnh báo / lỗi nhập liệu |
| `[I]` | Thông tin / không có dữ liệu |

---

## Kiểm thử

### Unit Tests (Doctest)

Project sử dụng framework **[doctest](https://github.com/doctest/doctest)** để viết unit tests. Các test file bao gồm:

| File test | Module được test |
|-----------|-----------------|
| `CustomStringTest.cpp` | Class `String` — constructor, so sánh, nối chuỗi, toInt, substring |
| `VectorTest.cpp` | Class `Vector<T>` — push_back, remove, copy/move, iterator |
| `SearchTest.cpp` | Tìm kiếm — tìm lớp, SV, điểm danh, case-insensitive |
| `SortTest.cpp` | Sắp xếp — QuickSort trên Vector, custom comparator |
| `ValidationTest.cpp` | Kiểm tra đầu vào — ngày, MSSV, trạng thái, mã lớp |
| `FileIOTest.cpp` | Đọc/ghi file — load/save lớp, SV, điểm danh |
| `DiemDanhManagerTest.cpp` | Nghiệp vụ — tính tỉ lệ vắng, sửa điểm danh |
| `BaoCaoTest.cpp` | Thống kê — xây dựng thống kê, sắp xếp top vắng |

### Chạy tests

```bash
cd build
cmake --build . --target Tests
cd ..
./build/Tests
```

## Dữ liệu mẫu

Project đi kèm bộ dữ liệu mẫu quy mô lớn, được sinh tự động bởi script Python [`test/gen_data.py`](test/gen_data.py):

| File | Số bản ghi | Mô tả |
|------|------------|-------|
| `data/lophoc.txt` | 50 lớp | 17 môn học, mỗi môn 2-3 lớp |
| `data/sinhvien.txt` | ~2,444 SV | 48-50 SV mỗi lớp |
| `data/diemdanh.txt` | ~33,779 phiếu | 12-15 buổi điểm danh mỗi lớp |

### Tái tạo dữ liệu mẫu

```bash
python test/gen_data.py
```

Seed cố định (`random.seed(42)`) đảm bảo kết quả tái tạo được (reproducible).

---

## Cấu trúc thư mục

```
diem-danh-sv/
├── CMakeLists.txt            # Cấu hình build CMake
├── README.md                 # Tài liệu này
├── .clang-format             # Cấu hình format code (Google style)
│
├── src/                      # Mã nguồn chính
│   ├── main.cpp              # Entry point, khởi tạo & menu loop
│   ├── Models.h              # Struct dữ liệu & enum
│   ├── CustomString.h/cpp    # Class String tự viết
│   ├── Vector.h              # Class Vector<T> template
│   ├── Sort.h                # Thuật toán QuickSort template
│   ├── FileIO.h/cpp          # Đọc/ghi file text
│   ├── Search.h/cpp          # Tìm kiếm & lọc dữ liệu
│   ├── Validation.h/cpp      # Kiểm tra & nhập liệu an toàn
│   ├── DiemDanhManager.h/cpp # Nghiệp vụ điểm danh
│   ├── BaoCao.h/cpp          # Thống kê & xuất báo cáo
│   └── Menu.h/cpp            # Giao diện console & sub-menus
│
├── data/                     # Dữ liệu ứng dụng (pipe-delimited text)
│   ├── lophoc.txt            # Danh sách lớp học
│   ├── sinhvien.txt          # Danh sách sinh viên
│   └── diemdanh.txt          # Phiếu điểm danh
│
├── test/                     # Unit tests & công cụ
│   ├── doctest.h             # Framework doctest (single-header)
│   ├── test_main.cpp         # Entry point cho test runner
│   ├── gen_data.py           # Script sinh dữ liệu mẫu (Python)
│   ├── CustomStringTest.cpp  # Tests cho CustomString
│   ├── VectorTest.cpp        # Tests cho Vector
│   ├── SearchTest.cpp        # Tests cho Search
│   ├── SortTest.cpp          # Tests cho Sort
│   ├── ValidationTest.cpp    # Tests cho Validation
│   ├── FileIOTest.cpp        # Tests cho FileIO
│   ├── DiemDanhManagerTest.cpp # Tests cho DiemDanhManager
│   └── BaoCaoTest.cpp        # Tests cho BaoCao
│
├── export/                   # Thư mục xuất báo cáo (tự tạo)
└── build/                    # Thư mục biên dịch (tự tạo)
```

---

## Tối ưu hóa biên dịch

CMake được cấu hình với các cờ tối ưu:

| Cờ | Mô tả |
|----|-------|
| `-O2` | Tối ưu tốc độ |
| `-march=native` | Tối ưu tập lệnh CPU (GCC/Clang) |
| `INTERPROCEDURAL_OPTIMIZATION` | Link-Time Optimization (LTO) |
| `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` | Bật đầy đủ cảnh báo |

---

## Code Style

- **Clang-Format**: Google style, indent 2 spaces, column limit 80
- **Ngôn ngữ giao diện**: Tiếng Việt không dấu (để tương thích mọi terminal)
- **Convention**: Comment bằng tiếng Việt, tên biến/hàm theo kiểu camelCase

---

## License

Đồ án học phần — Sử dụng cho mục đích học tập.
