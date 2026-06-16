#include "../src/CustomString.h"
#include <iostream>
#include <sstream>

// Hàm tiện ích để in nội dung và độ dài chuỗi
void printStr(const char* label, const String& s) {
    std::cout << label << ": \"" << s << "\" (length = " << s.length() << ")\n";
}

void testConstructor() {
    std::cout << "--- Testing Constructors & basic methods ---" << std::endl;
    
    String s1;
    std::cout << "Default constructor: empty() = " << (s1.empty() ? "true" : "false") << "\n";
    printStr("s1", s1);

    String s2("Hello");
    printStr("const char* constructor (s2)", s2);

    String s3(s2);
    printStr("Copy constructor (s3)", s3);

    String s4(std::move(s3));
    printStr("Move constructor (s4)", s4);
    printStr("s3 after move", s3);
}

void testAssignment() {
    std::cout << "\n--- Testing Assignment Operators ---" << std::endl;
    
    String s1("Test");
    String s2;
    s2 = s1; // Copy assignment
    printStr("Copy assignment (s2)", s2);

    String s3;
    s3 = std::move(s1); // Move assignment
    printStr("Move assignment (s3)", s3);
    printStr("s1 after move", s1);

    String s4;
    s4 = "C-String assignment";
    printStr("const char* assignment (s4)", s4);
}

void testElementAccess() {
    std::cout << "\n--- Testing Element Access ---" << std::endl;
    
    String s("World");
    printStr("Initial string", s);
    std::cout << "s[0]: " << s[0] << ", s[4]: " << s[4] << std::endl;
    
    s[0] = 'w';
    printStr("After s[0] = 'w'", s);
}

void testComparison() {
    std::cout << "\n--- Testing Comparison Operators ---" << std::endl;
    
    String s1("Apple");
    String s2("Banana");
    String s3("Apple");

    printStr("s1", s1);
    printStr("s2", s2);
    printStr("s3", s3);

    std::cout << "s1 == s3: " << (s1 == s3 ? "true" : "false") << std::endl;
    std::cout << "s1 != s2: " << (s1 != s2 ? "true" : "false") << std::endl;
    std::cout << "s1 < s2: " << (s1 < s2 ? "true" : "false") << std::endl;
    std::cout << "s2 > s1: " << (s2 > s1 ? "true" : "false") << std::endl;

    std::cout << "s1 == \"Apple\": " << (s1 == "Apple" ? "true" : "false") << std::endl;
    std::cout << "s1 != \"Banana\": " << (s1 != "Banana" ? "true" : "false") << std::endl;
}

void testConcatenation() {
    std::cout << "\n--- Testing Concatenation ---" << std::endl;

    String s1("Hello, ");
    String s2("World!");
    String s3 = s1 + s2;
    printStr("s1 + s2 (s3)", s3);

    String s4("Apples ");
    s4 += "and Oranges";
    printStr("s4 += \"and Oranges\"", s4);
    
    String s5("123");
    String s6("456");
    s5 += s6;
    printStr("s5 += s6", s5);
}

void testIOStreams() {
    std::cout << "\n--- Testing I/O Streams ---" << std::endl;

    std::stringstream ss;
    ss << "CustomStringInput";
    
    String s;
    ss >> s;
    printStr("Read from stream", s);

    std::stringstream ss2;
    ss2 << "Line 1\nLine 2";
    String line;
    getline(ss2, line);
    printStr("Getline", line);
}

void testEdgeCases() {
    std::cout << "\n--- Testing Edge Cases (Potential Crashes) ---" << std::endl;

    // 1. Khởi tạo với nullptr
    std::cout << "1. Constructor with nullptr: \n";
    String sNull(nullptr);
    printStr("  sNull", sNull);

    // 2. Gán chuỗi bằng nullptr
    std::cout << "2. Assignment with nullptr: \n";
    String sAssign("Data");
    sAssign = nullptr;
    printStr("  sAssign after nullptr assignment", sAssign);

    // 3. Tự gán chính nó (Self-assignment)
    std::cout << "3. Self-assignment (s = s): \n";
    String sSelf("SelfAssignment");
    sSelf = sSelf;
    printStr("  sSelf after sSelf = sSelf", sSelf);

    // 4. Tự nối chính nó (Self-concatenation)
    std::cout << "4. Self-concatenation (+ and +=): \n";
    String sConcat("A");
    sConcat = sConcat + sConcat;
    printStr("  sConcat after sConcat = sConcat + sConcat", sConcat);
    
    sConcat += sConcat;
    printStr("  sConcat after sConcat += sConcat", sConcat);

    // 5. So sánh với nullptr
    std::cout << "5. Comparison with nullptr: \n";
    String sComp("Test");
    std::cout << "  (sComp == nullptr) -> " << (sComp == nullptr ? "true" : "false") << std::endl;

    // 6. Truy cập ngoài giới hạn (Out of bounds) - Đã được comment lại để tránh crash hẳn chương trình khi chạy test
    std::cout << "6. Out of bounds access (UB): \n";
    std::cout << "  // String sOut(\"Hi\");\n";
    std::cout << "  // std::cout << sOut[10] << std::endl; // Sẽ gây ra lỗi Segmentation Fault\n";
}

int main() {
    std::cout << "========== CUSTOM STRING MANUAL TEST ==========\n" << std::endl;
    
    testConstructor();
    testAssignment();
    testElementAccess();
    testComparison();
    testConcatenation();
    testIOStreams();
    testEdgeCases();

    std::cout << "\n========== ALL TESTS COMPLETED ==========" << std::endl;
    return 0;
}
