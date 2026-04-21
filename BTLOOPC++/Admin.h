#pragma once
#include "NguoiDung.h"

class Admin : public NguoiDung {
public:
    Admin(std::string _id = "", std::string _name = "Admin", std::string _pass = "123")
        : NguoiDung(_id, _name, _pass) {
    }

    void displayMenu() const override;
};