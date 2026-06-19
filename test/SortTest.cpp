#include "doctest.h"
#include "../src/Sort.h"
#include "../src/CustomString.h"

TEST_CASE("Sort - Sắp xếp cơ bản") {
    SUBCASE("Mảng số nguyên") {
        Vector<int> v;
        v.push_back(5); v.push_back(2); v.push_back(8); v.push_back(1); v.push_back(3);
        
        Sort::sort(v);
        
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[2] == 3);
        CHECK(v[3] == 5);
        CHECK(v[4] == 8);
    }

    SUBCASE("Sắp xếp giảm dần (Custom Comparator)") {
        Vector<int> v;
        v.push_back(5); v.push_back(2); v.push_back(8); v.push_back(1); v.push_back(3);
        
        Sort::sort(v, [](const int& a, const int& b) { return a > b; });
        
        CHECK(v[0] == 8);
        CHECK(v[1] == 5);
        CHECK(v[2] == 3);
        CHECK(v[3] == 2);
        CHECK(v[4] == 1);
    }
}

TEST_CASE("Sort - Edge Cases") {
    SUBCASE("Mảng rỗng") {
        Vector<int> v;
        Sort::sort(v); // Không được crash
        CHECK(v.size() == 0);
    }

    SUBCASE("Mảng 1 phần tử") {
        Vector<int> v;
        v.push_back(42);
        Sort::sort(v);
        CHECK(v[0] == 42);
        CHECK(v.size() == 1);
    }

    SUBCASE("Mảng đã được sắp xếp sẵn") {
        Vector<int> v;
        for (int i = 0; i < 10; ++i) v.push_back(i);
        Sort::sort(v);
        for (int i = 0; i < 10; ++i) CHECK(v[i] == i);
    }

    SUBCASE("Mảng sắp xếp ngược") {
        Vector<int> v;
        for (int i = 10; i > 0; --i) v.push_back(i);
        Sort::sort(v);
        for (int i = 0; i < 10; ++i) CHECK(v[i] == i + 1);
    }

    SUBCASE("Mảng tất cả phần tử giống nhau") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i) v.push_back(7);
        Sort::sort(v);
        for (int i = 0; i < 5; ++i) CHECK(v[i] == 7);
    }
}

TEST_CASE("Sort - Stress Test (Hoare Quicksort & Insertion Sort fallback)") {
    Vector<int> v;
    // Chèn 1000 phần tử ngẫu nhiên (hoặc giảm dần xen kẽ) để kích hoạt Quicksort cắt phân hoạch
    for (int i = 0; i < 1000; ++i) {
        v.push_back((i % 2 == 0) ? i : 1000 - i);
    }
    
    Sort::sort(v);
    
    bool is_sorted = true;
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i+1]) {
            is_sorted = false;
            break;
        }
    }
    CHECK(is_sorted == true);
}

TEST_CASE("Sort - Kiểu dữ liệu phức tạp") {
    struct Item {
        int id;
        String name;
    };

    Vector<Item> v;
    Item i1; i1.id = 2; i1.name = "B"; v.push_back(std::move(i1));
    Item i2; i2.id = 1; i2.name = "A"; v.push_back(std::move(i2));
    Item i3; i3.id = 3; i3.name = "C"; v.push_back(std::move(i3));

    Sort::sort(v, [](const Item& a, const Item& b) {
        return a.id < b.id;
    });

    CHECK(v[0].id == 1);
    CHECK(v[1].id == 2);
    CHECK(v[2].id == 3);
    CHECK(v[0].name == "A");
}