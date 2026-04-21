#include "NguoiChoi.h"
#include <iostream>

NguoiChoi::NguoiChoi() {
    name = "";
    setPass("");
    kyLuc = 0;
    setRole("Player");
}

NguoiChoi::NguoiChoi(std::string _id, std::string _name, std::string _pass, int _kyLuc)
    : NguoiDung(_id, _name, _pass), kyLuc(_kyLuc) {
    setRole("Player");
}

NguoiChoi::NguoiChoi(const NguoiChoi& other)
    : NguoiDung(other.id, other.name, other.getPass()), kyLuc(other.kyLuc) {
    setRole(other.getRole());
}

NguoiChoi::~NguoiChoi() {
}

int NguoiChoi::getKyLuc() const {
    return kyLuc;
}

void NguoiChoi::setKyLuc(int _kyLuc) {
    if (_kyLuc > kyLuc) {
        kyLuc = _kyLuc;
    }
}

void NguoiChoi::displayMenu() const {
    std::cout << std::string(20, '-') << " MENU " << std::string(20, '-') << '\n';
    std::cout << "1. Choi tro choi\n";
    std::cout << "2. Xem ky luc\n";
    std::cout << "3. Dang xuat\n";
    std::cout << "0. Thoat\n";
}

std::ostream& operator<<(std::ostream& out, const NguoiChoi& nc) {
    out << "[Nguoi choi: " << nc.getName() << " | Ky luc: " << nc.kyLuc << "]";
    return out;
}

bool NguoiChoi::operator>(const NguoiChoi& other) const {
    return kyLuc > other.kyLuc;
}