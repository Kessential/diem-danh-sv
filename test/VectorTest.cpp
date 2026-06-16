#include "doctest.h"
#include <string>
#include <stdexcept>
#include <vector>
#include "../src/Vector.h"

// =========================================================
// CLASS 1: Dùng để test rò rỉ bộ nhớ (Memory Leak)
// =========================================================
struct Tracker {
    static int alive_count; 
    int id;

    Tracker(int i = 0) : id(i) { alive_count++; }
    Tracker(const Tracker& other) : id(other.id) { alive_count++; }
    Tracker(Tracker&& other) noexcept : id(other.id) { alive_count++; }
    Tracker& operator=(const Tracker& other) { id = other.id; return *this; }
    Tracker& operator=(Tracker&& other) noexcept { id = other.id; return *this; }
    ~Tracker() { alive_count--; }
};
int Tracker::alive_count = 0;

// =========================================================
// CLASS 2: Dùng để giả lập lỗi khi Copy
// =========================================================
struct ThrowingClass {
    int val;
    ThrowingClass(int v = 0) : val(v) {}
    
    ThrowingClass& operator=(const ThrowingClass& other) {
        if (other.val == -1) {
            throw std::runtime_error("Loi copy! Gia lap may tinh het RAM hoac loi xay ra.");
        }
        val = other.val;
        return *this;
    }
};

TEST_CASE("Vector - Co ban va Edge Cases") {
    Vector<int> v;
    
    // Pop back khi rỗng không crash
    v.pop_back(); 
    v.pop_back();
    CHECK(v.size() == 0);

    // Gọi back() khi rỗng là Undefined Behavior trong Vector này, không test Exception.
    // CHECK_THROWS_AS(v.back(), std::out_of_range);

    // Clear khi rỗng an toàn
    v.clear();
    CHECK(v.size() == 0);
}

TEST_CASE("Vector - Memory Leak") {
    Tracker::alive_count = 0;

    {
        Vector<Tracker> v;
        v.push_back(Tracker(1));
        v.push_back(Tracker(2));
        v.push_back(Tracker(3));
        
        CHECK(Tracker::alive_count == v.capacity()); // Vector dùng new T[] nên alive_count = capacity
        
        v.pop_back();
        CHECK(Tracker::alive_count == v.capacity());

        v.clear();
        CHECK(Tracker::alive_count == v.capacity());
        
        v.push_back(Tracker(4));
        v.push_back(Tracker(5));
    }

    CHECK(Tracker::alive_count == 0);
}

TEST_CASE("Vector - Tu gan va Copy/Move") {
    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    v1 = v1; 
    CHECK(v1.size() == 2);
    CHECK(v1[0] == 10);

    v1 = std::move(v1);
    CHECK(v1.size() == 2);
    CHECK(v1[1] == 20);
}



TEST_CASE("Vector - Crash & UB Edge Cases") {
    Vector<int> v_empty1;
    Vector<int> v_empty2(v_empty1);
    Vector<int> v_empty3;
    v_empty3 = v_empty1; 
    Vector<int> v_empty4(std::move(v_empty2)); 
    Vector<int> v_empty5;
    v_empty5 = std::move(v_empty3);
    CHECK(v_empty5.size() == 0);

    Vector<int> v_chain;
    v_chain.push_back(1);
    v_chain = v_chain = v_chain;
    CHECK(v_chain.size() == 1);
    CHECK(v_chain[0] == 1);

    Vector<int> v_reused;
    for (int i = 0; i < 1000; ++i) v_reused.push_back(i);
    v_reused.clear();
    v_reused.push_back(999);
    CHECK(v_reused.size() == 1);
    CHECK(v_reused[0] == 999);

    Vector<int> v_underflow;
    v_underflow.push_back(1);
    v_underflow.pop_back(); 
    v_underflow.pop_back(); 
    CHECK(v_underflow.size() == 0);
}

TEST_CASE("Vector - Kieu du lieu STL") {
    Vector<std::string> v_str;
    std::string long_str = "Mot chuoi cuc ky dai de test viec cap phat tren Heap cua std::string tranh viec bi SS0 (Small String Optimization) che mat loi";
    v_str.push_back(long_str);
    v_str.push_back(std::move(long_str));
    v_str.pop_back();
    v_str.clear();
    CHECK(v_str.size() == 0);

    Vector<std::vector<int>> v_vec;
    std::vector<int> stl_v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    v_vec.push_back(stl_v1); 
    v_vec.push_back(std::vector<int>{11, 12, 13, 14, 15}); 
    
    Vector<std::vector<int>> v_vec_copy = v_vec; 
    Vector<std::vector<int>> v_vec_assign;
    v_vec_assign = v_vec_copy; 
    
    v_vec.pop_back(); 
    CHECK(v_vec.size() == 1);
}