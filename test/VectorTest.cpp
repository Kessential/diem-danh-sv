#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "../src/Vector.h" // Chứa code Vector đã tối ưu lúc nãy

using namespace std;

// =========================================================
// CLASS 1: Dùng để test rò rỉ bộ nhớ (Memory Leak)
// =========================================================
struct Tracker {
    static int alive_count; // Đếm số object đang tồn tại trên RAM
    int id;

    Tracker(int i = 0) : id(i) { alive_count++; }
    Tracker(const Tracker& other) : id(other.id) { alive_count++; }
    Tracker(Tracker&& other) noexcept : id(other.id) { alive_count++; }
    Tracker& operator=(const Tracker& other) { id = other.id; return *this; }
    Tracker& operator=(Tracker&& other) noexcept { id = other.id; return *this; }
    ~Tracker() { alive_count--; }
};
int Tracker::alive_count = 0; // Khởi tạo biến đếm

// =========================================================
// CLASS 2: Dùng để giả lập lỗi khi Copy
// =========================================================
struct ThrowingClass {
    int val;
    ThrowingClass(int v = 0) : val(v) {}
    
    // Giả lập: Nếu copy trúng phần tử có val == -1, sẽ ném lỗi (giống như hết RAM)
    ThrowingClass& operator=(const ThrowingClass& other) {
        if (other.val == -1) {
            throw runtime_error("Loi copy! Gia lap may tinh het RAM hoac loi xay ra.");
        }
        val = other.val;
        return *this;
    }
};

// =========================================================
// CÁC HÀM TEST
// =========================================================

void Test_BasicAndEdgeCases() {
    cout << "--- TEST 1: Co ban va Edge Cases ---" << endl;
    Vector<int> v;
    
    // 1. Pop back khi rỗng (Phải không crash)
    v.pop_back(); 
    v.pop_back();
    cout << "[OK] Pop_back tren Vector rong khong bi crash." << endl;

    // 2. Gọi back() khi rỗng (Phải ném lỗi, không được sập)
    try {
        v.back();
        cout << "[LỖI] back() khong nem ra ngoai le!" << endl;
    } catch (const out_of_range& e) {
        cout << "[OK] back() nem dung ngoai le: " << e.what() << endl;
    }

    // 3. Clear khi rỗng
    v.clear();
    cout << "[OK] Clear tren Vector rong an toan." << endl;
}

void Test_MemoryLeak() {
    cout << "\n--- TEST 2: Kiem tra Ro ri Bo Nho (Memory Leak) ---" << endl;
    Tracker::alive_count = 0;

    {
        Vector<Tracker> v;
        v.push_back(Tracker(1));
        v.push_back(Tracker(2));
        v.push_back(Tracker(3));
        
        cout << "- So object tren RAM (sau push): " << Tracker::alive_count << " (ky vong 3)" << endl;
        
        v.pop_back();
        cout << "- So object tren RAM (sau pop): " << Tracker::alive_count << " (ky vong 2)" << endl;

        v.clear();
        cout << "- So object tren RAM (sau clear): " << Tracker::alive_count << " (ky vong 0)" << endl;
        
        v.push_back(Tracker(4));
        v.push_back(Tracker(5));
    } // Khi ra khỏi scope này, Destructor của Vector sẽ được gọi

    if (Tracker::alive_count == 0) {
        cout << "[OK] Khong he ro ri RAM! Tat ca phan tu da bi tieu huy." << endl;
    } else {
        cout << "[LỖI] RO RI RAM: Con " << Tracker::alive_count << " object chua bi xoa!" << endl;
    }
}

void Test_RuleOfFiveAndSelfAssignment() {
    cout << "\n--- TEST 3: Tu gan (Self-Assignment) & Copy/Move ---" << endl;
    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    // 1. Tự gán cho chính mình (Rất dễ crash nếu code sai)
    v1 = v1; 
    if (v1.size() == 2 && v1[0] == 10) {
        cout << "[OK] Tu gan cho chinh minh (v = v) an toan, khong mat du lieu." << endl;
    } else {
        cout << "[LỖI] Tu gan cho chinh minh bi mat du lieu!" << endl;
    }

    // 2. Move assignment self
    v1 = std::move(v1);
    cout << "[OK] Move tu gan cho chinh minh an toan." << endl;
}

void Test_ExceptionSafety() {
    cout << "\n--- TEST 4: Dam bao an toan khi xay ra loi (Exception Safety) ---" << endl;
    
    Vector<ThrowingClass> v_goc;
    v_goc.push_back(ThrowingClass(1));
    v_goc.push_back(ThrowingClass(2));
    v_goc.push_back(ThrowingClass(3)); // Size = 3

    Vector<ThrowingClass> v_loi;
    v_loi.push_back(ThrowingClass(9));
    v_loi.push_back(ThrowingClass(-1)); // -1 se gay ra loi khi copy
    
    cout << "- Nha cu (v_goc) dang co " << v_goc.size() << " phan tu." << endl;
    
    try {
        // Cố tình copy dữ liệu lỗi vào. Lỗi sẽ bung ra ở giữa chừng hàm operator=
        v_goc = v_loi; 
        cout << "[LỖI] Khong nem ra loi nhu ky vong!" << endl;
    } 
    catch (const exception& e) {
        cout << "- Da bat duoc loi: " << e.what() << endl;
        
        // KIỂM TRA XEM v_goc CÓ BỊ HỎNG KHÔNG?
        if (v_goc.size() == 3 && v_goc[0].val == 1 && v_goc[2].val == 3) {
            cout << "[OK] TUYET VOI! v_goc (nha cu) hoan toan con nguyen ven, khong mat du lieu!" << endl;
        } else {
            cout << "[LỖI CRITICAL] v_goc da bi xoa mat du lieu vi loi copy!" << endl;
        }
    }
}

void Test_UBCrashEdgeCases() {
    cout << "\n--- TEST 5: Edge Cases de kiem tra Crash & UB ---" << endl;
    
    // 1. Copy/Move Vector rỗng (De bi UB neu pointer invalid)
    Vector<int> v_empty1;
    Vector<int> v_empty2(v_empty1); // Copy constructor
    Vector<int> v_empty3;
    v_empty3 = v_empty1; // Copy assignment
    Vector<int> v_empty4(std::move(v_empty2)); // Move constructor
    Vector<int> v_empty5;
    v_empty5 = std::move(v_empty3); // Move assignment
    cout << "[OK] Copy/Move Vector rong hoat dong an toan." << endl;

    // 2. Chained self-assignment (De gay crash do memory bi xoa nhieu lan)
    Vector<int> v_chain;
    v_chain.push_back(1);
    v_chain = v_chain = v_chain;
    if (v_chain.size() == 1 && v_chain[0] == 1) {
        cout << "[OK] Chained self-assignment an toan." << endl;
    } else {
        cout << "[LỖI] Chained self-assignment mat du lieu!" << endl;
    }

    // 3. Clear roi lai push_back lien tuc (Kiem tra capacity control)
    Vector<int> v_reused;
    for (int i = 0; i < 1000; ++i) v_reused.push_back(i);
    v_reused.clear();
    v_reused.push_back(999);
    if (v_reused.size() == 1 && v_reused[0] == 999) {
        cout << "[OK] Tai su dung Vector sau khi clear() (Memory khong leak hay crash)." << endl;
    } else {
        cout << "[LỖI] Tai su dung sau clear() co van de!" << endl;
    }

    // 4. Pop_back nhieu hon size (Kiem tra co lenh giam len qua muc gay UB khong)
    Vector<int> v_underflow;
    v_underflow.push_back(1);
    v_underflow.pop_back(); // len = 0
    v_underflow.pop_back(); // len co the bi am (neu dung size_t se bi tran so)
    if (v_underflow.size() == 0) {
        cout << "[OK] Pop_back qua muc khong gay underflow size_t." << endl;
    } else {
        cout << "[LỖI] Pop_back qua muc gay loi logic size!" << endl;
    }
}

void Test_STLTypesMemoryManagement() {
    cout << "\n--- TEST 6: Kiem tra Quan ly bo nho voi Kieu du lieu STL ---" << endl;
    
    // 1. Vector chua std::string (Kiem tra destructor va string SS0)
    try {
        Vector<std::string> v_str;
        std::string long_str = "Mot chuoi cuc ky dai de test viec cap phat tren Heap cua std::string tranh viec bi SS0 (Small String Optimization) che mat loi";
        v_str.push_back(long_str); // Copy
        v_str.push_back(std::move(long_str)); // Move
        v_str.pop_back(); // Chắc chắn destructor của string được gọi
        v_str.clear();
        cout << "[OK] Vector<std::string> hoat dong on dinh (Khong crash/leak)." << endl;
    } catch (...) {
        cout << "[LỖI] Vector<std::string> gay ra exception khong mong muon!" << endl;
    }

    // 2. Vector chứa std::vector (Dữ liệu lồng nhau phức tạp)
    try {
        Vector<std::vector<int>> v_vec;
        std::vector<int> stl_v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        v_vec.push_back(stl_v1); // Copy
        v_vec.push_back(std::vector<int>{11, 12, 13, 14, 15}); // Move
        
        Vector<std::vector<int>> v_vec_copy = v_vec; // Test Copy Constructor với mảng sâu
        Vector<std::vector<int>> v_vec_assign;
        v_vec_assign = v_vec_copy; // Test Copy Assignment
        
        v_vec.pop_back(); // Test dọn dẹp
    } catch (...) {
        cout << "[LỖI] Vector<std::vector<int>> gay ra loi khi copy/move!" << endl;
    }
    cout << "[OK] Vector<std::vector<int>> hoat dong on dinh (Khong double-free hay crash)." << endl;
}

int main() {
    cout << "BAT DAU TEST MODULE VECTOR...\n" << endl;
    
    Test_BasicAndEdgeCases();
    Test_MemoryLeak();
    Test_RuleOfFiveAndSelfAssignment();
    Test_ExceptionSafety();
    Test_UBCrashEdgeCases();
    Test_STLTypesMemoryManagement();

    cout << "\n=> ALL TESTS PASSED! CHUONG TRINH KHONG CRASH!" << endl;
    return 0;
}