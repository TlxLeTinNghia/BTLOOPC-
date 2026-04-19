#include "NguoiDung.h"

int NguoiDung::userCount = 0;

NguoiDung::NguoiDung() {
    ++userCount;
    id = "ND" + std::to_string(userCount);
    name = "Unknown";
    password = "";
    role = "Player";
}

NguoiDung::NguoiDung(std::string _id, std::string _name, std::string _password) {
    ++userCount;
    if (_id.empty()) {
        id = "ND" + std::to_string(userCount);
    }
    else {
        id = _id;
    }
    name = _name;
    password = _password;
    role = "Player";
}

NguoiDung::~NguoiDung() {
    --userCount;
}

std::string NguoiDung::getId() const {
    return id;
}

std::string NguoiDung::getName() const {
    return name;
}

std::string NguoiDung::getPass() const {
    return password;
}

std::string NguoiDung::getRole() const {
    return role;
}

void NguoiDung::setName(const std::string& newName) {
    name = newName;
}

void NguoiDung::setPass(const std::string& newPass) {
    password = newPass;
}

void NguoiDung::setRole(const std::string& newRole) {
    role = newRole;
}

bool NguoiDung::operator==(const NguoiDung& other) const {
    return name == other.name && password == other.password;
}