cmake_minimum_required(VERSION 3.10)

# Tên dự án
project(KTLT_DiemDanh VERSION 1.0 LANGUAGES CXX)

# Yêu cầu C++17 trở lên
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Bắt buộc chỉ dùng cấu hình Release
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Supported configurations" FORCE)

if(MSVC)
    add_compile_options(/O2)
else()
    add_compile_options(-O2)
endif()

# Chỉ bao gồm thư mục src
include_directories(src)

# Các file mã nguồn
set(SOURCES
    src/main.cpp
    src/CustomString.cpp
    src/Search.cpp
    src/FileIO.cpp
    src/Validation.cpp
    src/DiemDanhManager.cpp
    src/BaoCao.cpp
    src/Menu.cpp
)

# Ứng dụng chính
add_executable(diemdanh ${SOURCES})
