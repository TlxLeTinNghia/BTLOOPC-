#include "Admin.h"
#include <iostream>

void Admin::displayMenu() const {
    std::cout << std::string(20, '-') << " ADMIN MENU " << std::string(20, '-') << '\n';
    std::cout << "1. Them cau hoi\n";
    std::cout << "2. Sua cau hoi\n";
    std::cout << "3. Xoa cau hoi\n";
    std::cout << "4. Xem tat ca cau hoi\n";
    std::cout << "5. Xem cau hinh game\n";
    std::cout << "6. Dang xuat\n";
}