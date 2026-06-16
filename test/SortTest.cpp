#include "doctest.h"
#include <string>
#include <vector>
#include "../src/Vector.h"
#include "../src/Sort.h"

template <typename T>
bool is_sorted_custom(const Vector<T>& arr) {
    if (arr.size() <= 1) return true;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i + 1] < arr[i]) return false;
    }
    return true;
}

TEST_CASE("Sort - Mang co ban") {
    Vector<int> empty_arr;
    Sort::sort(empty_arr);
    CHECK(is_sorted_custom(empty_arr));

    Vector<int> single_arr;
    single_arr.push_back(42);
    Sort::sort(single_arr);
    CHECK(is_sorted_custom(single_arr));
}

TEST_CASE("Sort - Mang dac biet") {
    Vector<int> reverse_arr;
    for (int i = 1000; i > 0; --i) reverse_arr.push_back(i);
    Sort::sort(reverse_arr);
    CHECK(is_sorted_custom(reverse_arr));

    Vector<int> all_same_arr;
    for (int i = 0; i < 1000; ++i) all_same_arr.push_back(7);
    Sort::sort(all_same_arr);
    CHECK(is_sorted_custom(all_same_arr));
}

TEST_CASE("Sort - Kieu du lieu STL (std::string)") {
    Vector<std::string> str_arr;
    str_arr.push_back("Zebra");
    str_arr.push_back("Apple");
    str_arr.push_back("Mango");
    str_arr.push_back("Banana");
    str_arr.push_back("Orange");
    str_arr.push_back("Apple");
    Sort::sort(str_arr);
    CHECK(is_sorted_custom(str_arr));
}

TEST_CASE("Sort - Gia tri gioi han & Rang cua") {
    Vector<int> limits_arr;
    limits_arr.push_back(2147483647);
    limits_arr.push_back(-2147483648);
    limits_arr.push_back(0);
    limits_arr.push_back(-1);
    limits_arr.push_back(1);
    Sort::sort(limits_arr);
    CHECK(is_sorted_custom(limits_arr));

    Vector<int> interleaved_arr;
    for (int i = 0; i < 500; ++i) {
        interleaved_arr.push_back(10000 - i);
        interleaved_arr.push_back(i);
    }
    Sort::sort(interleaved_arr);
    CHECK(is_sorted_custom(interleaved_arr));
}

TEST_CASE("Sort - Kieu std::vector") {
    Vector<std::vector<int>> vec_of_vec;
    vec_of_vec.push_back({10, 20, 30});
    vec_of_vec.push_back({1, 2});
    vec_of_vec.push_back({5, 5, 5, 5});
    vec_of_vec.push_back({10, 20});
    vec_of_vec.push_back({0});
    Sort::sort(vec_of_vec);
    CHECK(is_sorted_custom(vec_of_vec));
}