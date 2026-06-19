#include "doctest.h"
#include "../src/Vector.h"
#include "../src/CustomString.h"
#include <string>

// Lớp hỗ trợ kiểm tra Memory Leak
struct MemoryTracker {
    static int alive_count;
    int data;

    MemoryTracker(int d = 0) : data(d) { alive_count++; }
    MemoryTracker(const MemoryTracker& other) : data(other.data) { alive_count++; }
    MemoryTracker(MemoryTracker&& other) noexcept : data(other.data) { alive_count++; }
    MemoryTracker& operator=(const MemoryTracker& other) { data = other.data; return *this; }
    MemoryTracker& operator=(MemoryTracker&& other) noexcept { data = other.data; return *this; }
    ~MemoryTracker() { alive_count--; }
};
int MemoryTracker::alive_count = 0;

TEST_CASE("Vector - Khởi tạo và cơ bản") {
    Vector<int> v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);
    CHECK(v.empty() == true);

    v.push_back(10);
    CHECK(v.size() == 1);
    CHECK(v.capacity() >= 1);
    CHECK(v.empty() == false);
    CHECK(v[0] == 10);
}

TEST_CASE("Vector - Thêm và Xóa phần tử (push_back, pop_back, remove, clear)") {
    Vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i * 10);
    }
    CHECK(v.size() == 5);
    CHECK(v.capacity() >= 5);

    SUBCASE("Pop back") {
        v.pop_back();
        CHECK(v.size() == 4);
        CHECK(v.back() == 30);
    }

    SUBCASE("Pop back quá mức (dưới 0)") {
        v.clear();
        v.pop_back(); // Phải an toàn, không crash
        CHECK(v.size() == 0);
    }

    SUBCASE("Remove phần tử ở giữa") {
        v.remove(2); // Xóa 20
        CHECK(v.size() == 4);
        CHECK(v[2] == 30);
    }

    SUBCASE("Remove phần tử ngoài phạm vi") {
        v.remove(10); // Phải an toàn, không đổi
        CHECK(v.size() == 5);
    }

    SUBCASE("Clear vector") {
        v.clear();
        CHECK(v.size() == 0);
        CHECK(v.empty() == true);
    }
}

TEST_CASE("Vector - Copy và Move Semantics") {
    Vector<int> v1;
    v1.push_back(1); v1.push_back(2);

    SUBCASE("Copy constructor") {
        Vector<int> v2(v1);
        CHECK(v2.size() == 2);
        CHECK(v2[0] == 1);
        v2[0] = 99;
        CHECK(v1[0] == 1); // Deep copy
    }

    SUBCASE("Copy assignment") {
        Vector<int> v2;
        v2 = v1;
        CHECK(v2.size() == 2);
        v2[1] = 99;
        CHECK(v1[1] == 2);
    }

    SUBCASE("Tự gán (Self-assignment)") {
        v1 = v1;
        CHECK(v1.size() == 2);
        CHECK(v1[0] == 1);
    }

    SUBCASE("Move constructor") {
        Vector<int> v2(std::move(v1));
        CHECK(v2.size() == 2);
        CHECK(v1.size() == 0);
        CHECK(v1.capacity() == 0);
    }

    SUBCASE("Move assignment") {
        Vector<int> v2;
        v2 = std::move(v1);
        CHECK(v2.size() == 2);
        CHECK(v1.size() == 0);
    }
}

TEST_CASE("Vector - Iterator") {
    Vector<int> v;
    v.push_back(10); v.push_back(20); v.push_back(30);

    int sum = 0;
    for (auto val : v) {
        sum += val;
    }
    CHECK(sum == 60);
}

TEST_CASE("Vector - Quản lý bộ nhớ (Tránh Memory Leak)") {
    MemoryTracker::alive_count = 0;
    {
        Vector<MemoryTracker> v;
        v.push_back(MemoryTracker(1));
        v.push_back(MemoryTracker(2));
        
        // Vì Vector cấp phát theo capacity, số alive_count = capacity (khởi tạo default)
        CHECK(MemoryTracker::alive_count == v.capacity());

        v.pop_back();
        CHECK(MemoryTracker::alive_count == v.capacity()); // Xóa logic, bộ nhớ vật lý vẫn giữ
        
        Vector<MemoryTracker> v2(v); // Copy
        CHECK(MemoryTracker::alive_count == v.capacity() + v2.capacity());
    }
    // Khi thoát block, tất cả phải được hủy
    CHECK(MemoryTracker::alive_count == 0);
}

TEST_CASE("Vector - Crash & UB Edge Cases") {
    Vector<int> v_empty;
    Vector<int> v_copy_empty(v_empty);
    CHECK(v_copy_empty.size() == 0);
    
    v_copy_empty = v_empty;
    CHECK(v_copy_empty.size() == 0);

    // Chèn liên tục rất nhiều phần tử để test grow
    Vector<int> v_grow;
    for(int i = 0; i < 10000; i++) {
        v_grow.push_back(i);
    }
    CHECK(v_grow.size() == 10000);
    CHECK(v_grow[9999] == 9999);
}

TEST_CASE("Vector - Kieu du lieu CustomString") {
    SUBCASE("Them va xoa chuoi dai de kiem tra memory leak") {
        Vector<String> v_str;
        
        // Them cac chuoi dai de bat buoc String phai cap phat dong tren heap
        String long_str1("Mot chuoi rat dai thu nhat de kiem tra viec cap phat bo nho tren heap cua CustomString");
        String long_str2("Mot chuoi rat dai thu hai cung voi muc dich tuong tu nham tranh SSO (Small String Optimization) neu co");
        
        v_str.push_back(long_str1);
        v_str.push_back(long_str2);
        
        CHECK(v_str.size() == 2);
        CHECK(v_str[0] == long_str1);
        CHECK(v_str[1] == long_str2);
        
        v_str.pop_back();
        CHECK(v_str.size() == 1);
        CHECK(v_str[0] == long_str1);
        
        v_str.clear();
        CHECK(v_str.size() == 0);
    }

    SUBCASE("Copy va Move Semantics voi CustomString") {
        Vector<String> v1;
        v1.push_back(String("String A"));
        v1.push_back(String("String B"));
        
        Vector<String> v2 = v1; // Copy constructor
        CHECK(v2.size() == 2);
        CHECK(v2[0] == "String A");
        CHECK(v2[1] == "String B");
        
        v2[0] = String("Modified A");
        CHECK(v1[0] == "String A"); // v1 khong bi thay doi
        
        Vector<String> v3;
        v3 = std::move(v2); // Move assignment
        CHECK(v3.size() == 2);
        CHECK(v3[0] == "Modified A");
        CHECK(v2.size() == 0); // v2 da bi move
        
        // Tu move
        Vector<String>& v3_ref = v3;
        v3 = std::move(v3_ref);
        CHECK(v3.size() == 2);
        CHECK(v3[0] == "Modified A");
    }
    
    SUBCASE("Vector<Vector<String>> Edge Cases") {
        Vector<Vector<String>> v_2d;
        Vector<String> row1;
        row1.push_back("A1");
        row1.push_back("A2");
        
        v_2d.push_back(row1); // Copy
        CHECK(v_2d.size() == 1);
        CHECK(v_2d[0][0] == "A1");
        
        v_2d.push_back(std::move(row1)); // Move
        CHECK(v_2d.size() == 2);
        CHECK(row1.size() == 0);
        
        v_2d.clear();
        CHECK(v_2d.size() == 0);
    }
}