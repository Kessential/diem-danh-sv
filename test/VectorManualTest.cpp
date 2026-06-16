#include <iostream>
#include "../src/Vector.h"
#include "../src/CustomString.h"

void testPrimitiveType() {
    std::cout << "========================================" << std::endl;
    std::cout << "=== Test with Primitive Type (int) ===" << std::endl;
    std::cout << "========================================" << std::endl;
    Vector<int> vec;
    std::cout << "Initial size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    
    std::cout << "Pushing elements: 1, 2, 3, 4, 5" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }
    std::cout << "Size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    
    std::cout << "Elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Testing remove index 2 (value 3):" << std::endl;
    vec.remove(2);
    std::cout << "Elements after remove: ";
    for (auto& x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing pop_back():" << std::endl;
    vec.pop_back();
    std::cout << "Elements after pop_back: ";
    for (auto& x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing clear():" << std::endl;
    vec.clear();
    std::cout << "Size after clear: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    std::cout << std::endl;
}

void testCustomString() {
    std::cout << "========================================" << std::endl;
    std::cout << "=== Test with CustomString ===" << std::endl;
    std::cout << "========================================" << std::endl;
    Vector<String> vec;
    
    std::cout << "Pushing strings: 'Hello', 'World', 'C++'" << std::endl;
    vec.push_back(String("Hello"));
    vec.push_back(String("World"));
    vec.push_back(String("C++"));
    
    std::cout << "Elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Testing remove index 1 ('World'):" << std::endl;
    vec.remove(1);
    std::cout << "Elements after remove: ";
    for (auto& x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing pop_back():" << std::endl;
    vec.pop_back();
    std::cout << "Elements after pop_back: ";
    for (auto& x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing copy constructor:" << std::endl;
    vec.push_back(String("Another"));
    Vector<String> vecCopy = vec;
    std::cout << "Copied elements: ";
    for (auto& x : vecCopy) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing assignment operator:" << std::endl;
    Vector<String> vecAssign;
    vecAssign = vec;
    std::cout << "Assigned elements: ";
    for (auto& x : vecAssign) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Testing clear():" << std::endl;
    vec.clear();
    std::cout << "Size after clear: " << vec.size() << std::endl;
    std::cout << std::endl;
}

void testSpecialCases() {
    std::cout << "=================================================" << std::endl;
    std::cout << "=== Test Special/Edge Cases (Crash Prevention) ===" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    std::cout << "1. pop_back on empty vector" << std::endl;
    Vector<String> emptyVec;
    emptyVec.pop_back(); // Should not crash
    std::cout << "   Size after pop_back on empty: " << emptyVec.size() << " (Expected: 0)" << std::endl;
    
    std::cout << "2. remove out of bounds on empty vector" << std::endl;
    emptyVec.remove(0); // Should not crash
    emptyVec.remove(100); // Should not crash
    std::cout << "   Size after remove out of bounds: " << emptyVec.size() << " (Expected: 0)" << std::endl;

    std::cout << "3. Huge resize (grow) test" << std::endl;
    Vector<String> hugeVec;
    for (int i = 0; i < 1000; ++i) {
        // String format: "Item"
        hugeVec.push_back(String("Item"));
    }
    std::cout << "   Pushed 1000 items. Size: " << hugeVec.size() << ", Capacity: " << hugeVec.capacity() << std::endl;
    
    std::cout << "4. Self assignment" << std::endl;
    hugeVec = hugeVec; // Should not crash or lose data
    std::cout << "   Size after self assignment: " << hugeVec.size() << " (Expected: 1000)" << std::endl;
    
    std::cout << "5. Copy empty vector" << std::endl;
    Vector<String> emptyCopy = emptyVec;
    std::cout << "   Empty copy size: " << emptyCopy.size() << " (Expected: 0)" << std::endl;
    
    std::cout << "6. Move constructor and move assignment" << std::endl;
    Vector<String> moveSrc;
    moveSrc.push_back(String("Moved"));
    Vector<String> moveDst(static_cast<Vector<String>&&>(moveSrc));
    std::cout << "   Move Dst size: " << moveDst.size() << " (Expected: 1), Move Src size: " << moveSrc.size() << " (Expected: 0)" << std::endl;
    
    Vector<String> moveAssignDst;
    moveAssignDst = static_cast<Vector<String>&&>(moveDst);
    std::cout << "   Move Assign Dst size: " << moveAssignDst.size() << " (Expected: 1), Move Dst size: " << moveDst.size() << " (Expected: 0)" << std::endl;
    
    std::cout << "7. Out of bounds index access (Manual test, just checking if valid within range)" << std::endl;
    if (moveAssignDst.size() > 0) {
        std::cout << "   Access valid index 0: " << moveAssignDst[0] << std::endl;
    }
    
    std::cout << "\nAll special cases executed without crashing!" << std::endl;
}

int main() {
    testPrimitiveType();
    testCustomString();
    testSpecialCases();
    return 0;
}
