cmake_minimum_required(VERSION 3.10)

project(KTLT_DiemDanh VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

include_directories(src)

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

add_executable(diemdanh ${SOURCES})

if(MSVC)
    target_compile_options(diemdanh PRIVATE
        /W4             
        /permissive-    
        /Zc:__cplusplus
        /utf-8
        /EHsc           
        $<$<CONFIG:Release>:/O2> # Thêm rõ ràng /O2 cho chế độ Release
    )

    target_compile_definitions(diemdanh PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(diemdanh PRIVATE
        -Wall
        -Wextra
        -Wpedantic  
        -Wshadow
        -Wconversion
        -O2
        -march=native   # Tối ưu hóa tập lệnh riêng cho CPU đang biên dịch (chỉ hỗ trợ MinGW/GCC/Clang)
    )
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)
if(ipo_supported)
    set_property(TARGET diemdanh PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
