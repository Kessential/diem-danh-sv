#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include "../src/Vector.h"
#include "../src/Sort.h"

// Hàm tự viết để thay thế std::is_sorted vì Vector chưa có iterator
template <typename T>
bool is_sorted_custom(const Vector<T>& arr) {
    if (arr.size() <= 1) return true;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        // Nếu phần tử đứng sau nhỏ hơn phần tử đứng trước -> Sai
        if (arr[i + 1] < arr[i]) return false;
    }
    return true;
}

// Hàm in kết quả
template <typename T>
void checkTest(const std::string& testName, const Vector<T>& arr) {
    if (is_sorted_custom(arr)) {
        std::cout << "[OK] " << testName << " - Da sap xep dung.\n";
    } else {
        std::cout << "[FAIL] " << testName << " - SAP XEP SAI!\n";
        exit(1); 
    }
}

int main() {
    std::cout << "=== BAT DAU KIEM THU MODULE SORT VOI CUSTOM VECTOR ===\n\n";

    // TEST 1: Mảng rỗng và mảng 1 phần tử
    Vector<int> empty_arr;
    Sort::sort(empty_arr);
    checkTest("Test 1a (Mang rong)", empty_arr);

    Vector<int> single_arr;
    single_arr.push_back(42);
    Sort::sort(single_arr);
    checkTest("Test 1b (Mang 1 phan tu)", single_arr);

    // TEST 2: Mảng đã sắp xếp sẵn 
    Vector<int> sorted_arr;
    for (int i = 0; i < 10000; ++i) sorted_arr.push_back(i);
    Sort::sort(sorted_arr);
    checkTest("Test 2 (Mang da sap xep san)", sorted_arr);

    // TEST 3: Mảng sắp xếp giảm dần 
    Vector<int> reverse_arr;
    for (int i = 10000; i > 0; --i) reverse_arr.push_back(i);
    Sort::sort(reverse_arr);
    checkTest("Test 3 (Mang sap xep giam dan)", reverse_arr);

    // TEST 4: Mảng chứa toàn các phần tử giống hệt nhau
    Vector<int> all_same_arr;
    for (int i = 0; i < 10000; ++i) all_same_arr.push_back(7);
    Sort::sort(all_same_arr);
    checkTest("Test 4 (Mang toan phan tu giong nhau)", all_same_arr);

    // TEST 5: Dữ liệu Ký tự (String) - Test Copy/Move Assignment của Vector
    Vector<std::string> str_arr;
    str_arr.push_back("Zebra");
    str_arr.push_back("Apple");
    str_arr.push_back("Mango");
    str_arr.push_back("Banana");
    str_arr.push_back("Orange");
    str_arr.push_back("Apple");
    Sort::sort(str_arr);
    checkTest("Test 5 (Mang Kieu String)", str_arr);

    // TEST 6: Stress Test 1.000.000 phần tử ngẫu nhiên
    std::cout << "\nDang chay Test 6 (Stress Test 1.000.000 phan tu)... Vui long doi\n";
    Vector<int> huge_arr;
    
    std::mt19937 rng(1337); 
    std::uniform_int_distribution<int> dist(1, 1000000);
    
    for (int i = 0; i < 1000000; ++i) {
        huge_arr.push_back(dist(rng));
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    Sort::sort(huge_arr);
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    checkTest("Test 6 (Mang Random khong lo)", huge_arr);
    std::cout << "Thoi gian chay Test 6: " << duration.count() << " ms\n";

    // TEST 7: Các giá trị giới hạn (Max, Min) và âm dương đan xen (Tránh tràn số/UB khi so sánh)
    Vector<int> limits_arr;
    limits_arr.push_back(2147483647);
    limits_arr.push_back(-2147483648);
    limits_arr.push_back(0);
    limits_arr.push_back(-1);
    limits_arr.push_back(1);
    Sort::sort(limits_arr);
    checkTest("Test 7 (Gia tri gioi han max/min & am/duong)", limits_arr);

    // TEST 8: Mảng hầu như giống nhau chỉ khác phần tử cuối hoặc đầu (Kiem tra Out-of-bounds UB)
    Vector<int> almost_same_arr;
    for (int i = 0; i < 5000; ++i) almost_same_arr.push_back(5);
    almost_same_arr.push_back(1); // Bé hơn ở cuối
    Sort::sort(almost_same_arr);
    checkTest("Test 8 (Mang giong nhau, khac phan tu cuoi)", almost_same_arr);

    Vector<int> almost_same_arr2;
    almost_same_arr2.push_back(9); // Lớn hơn ở đầu
    for (int i = 0; i < 5000; ++i) almost_same_arr2.push_back(5);
    Sort::sort(almost_same_arr2);
    checkTest("Test 9 (Mang giong nhau, khac phan tu dau)", almost_same_arr2);
    
    // TEST 10: Răng cưa (Interleaved) lớn bé đan xen (Test sort pivot selection de crash/UB)
    Vector<int> interleaved_arr;
    for (int i = 0; i < 1000; ++i) {
        interleaved_arr.push_back(10000 - i);
        interleaved_arr.push_back(i);
    }
    Sort::sort(interleaved_arr);
    checkTest("Test 10 (Mang rang cua lon/be dan xen)", interleaved_arr);

    // TEST 11: Mảng các std::vector (Kiem tra memory management khi hoán đổi đối tượng STL phức tạp)
    Vector<std::vector<int>> vec_of_vec;
    vec_of_vec.push_back({10, 20, 30});
    vec_of_vec.push_back({1, 2});
    vec_of_vec.push_back({5, 5, 5, 5});
    vec_of_vec.push_back({10, 20});
    vec_of_vec.push_back({0});
    Sort::sort(vec_of_vec);
    checkTest("Test 11 (Mang chua std::vector de test copy/swap mem leak)", vec_of_vec);

    std::cout << "\n=== TAT CA TEST PASS! HE THONG HOAT DONG HOAN HAO! ===\n";
    return 0;
}