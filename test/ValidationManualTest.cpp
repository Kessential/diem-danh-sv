#include "../src/Validation.h"
#include <iostream>
#include <string>

void inTieuDe(const char* title) {
    std::cout << "\n========================================\n";
    std::cout << " TEST: " << title << "\n";
    std::cout << "========================================\n";
}

int main() {
    std::cout << "CHAO MUNG BAN DEN VOI TRINH KIEM THU THU CONG MODULE VALIDATION\n";
    std::cout << "Trong chuong trinh nay, hay thu co tinh nhap sai (nhap qua 512 ky tu, \n"
              << "nhap chu vao o so, an Enter de trong) de kiem tra tinh ben bi!\n\n";

    // 1. Test nhapChuoi
    inTieuDe("Validation::nhapChuoi");
    std::cout << "[MUC TIEU]: Thu nhap chuoi rong, hoac copy paste > 512 ky tu.\n";
    String strDest;
    Validation::nhapChuoi("Hay nhap mot chuoi bat ky", strDest);
    std::cout << "-> Ket qua ghi nhan duoc: '" << strDest.c_str() << "'\n";

    // 2. Test nhapSoNguyen
    inTieuDe("Validation::nhapSoNguyen");
    std::cout << "[MUC TIEU]: Thu nhap chu cai, ky tu dac biet, hoac so ngoai khoang 1-100.\n";
    int intDest = Validation::nhapSoNguyen("Hay nhap mot so nguyen", 1, 100);
    std::cout << "-> Ket qua ghi nhan duoc: " << intDest << "\n";

    // 3. Test nhapTrangThai
    inTieuDe("Validation::nhapTrangThai");
    std::cout << "[MUC TIEU]: Thu nhap x, y, z hoac chuoi dai. Chi chap nhan C, P, hoac K.\n";
    char ttDest = Validation::nhapTrangThai("Sinh vien A");
    std::cout << "-> Ket qua ghi nhan duoc: '" << ttDest << "'\n";

    // 4. Test nhapXacNhan
    inTieuDe("Validation::nhapXacNhan");
    std::cout << "[MUC TIEU]: Thu nhap sai phim, Enter de trong hoac nhap chuoi dai 'yes'/'no'.\n";
    bool confirmDest = Validation::nhapXacNhan("Ban co muon tiep tuc khong?");
    std::cout << "-> Ket qua ghi nhan duoc: " << (confirmDest ? "True (Yes)" : "False (No)") << "\n";

    // 5. Test nhapChuoiCoBaoLuu
    inTieuDe("Validation::nhapChuoiCoBaoLuu");
    std::cout << "[MUC TIEU]: Thu an Enter ngay de test chuc nang Giu nguyen, hoac nhap chuoi moi.\n";
    String strBaoLuu = "GIA TRI CU";
    bool strChanged = Validation::nhapChuoiCoBaoLuu("Hay sua chuoi", strBaoLuu);
    std::cout << "-> Co thay doi khong? " << (strChanged ? "Co" : "Khong") << "\n";
    std::cout << "-> Ket qua chuoi sau khi xu ly: '" << strBaoLuu.c_str() << "'\n";

    // 6. Test nhapSoNguyenCoBaoLuu
    inTieuDe("Validation::nhapSoNguyenCoBaoLuu");
    std::cout << "[MUC TIEU]: Thu an Enter de Giu nguyen, hoac nhap ky tu linh tinh.\n";
    int intBaoLuu = 999;
    bool intChanged = Validation::nhapSoNguyenCoBaoLuu("Hay sua so", intBaoLuu, 1, 1000);
    std::cout << "-> Co thay doi khong? " << (intChanged ? "Co" : "Khong") << "\n";
    std::cout << "-> Ket qua so nguyen sau khi xu ly: " << intBaoLuu << "\n";

    std::cout << "\n========================================\n";
    std::cout << " HOAN THANH KIEM THU THU CONG!\n";
    std::cout << "========================================\n";

    return 0;
}
