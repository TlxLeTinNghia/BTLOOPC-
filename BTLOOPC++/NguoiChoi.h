#pragma once
#include "NguoiDung.h"
#include <iostream>

class NguoiChoi : public NguoiDung {
private:
    int kyLuc;

public:
    NguoiChoi() {
        name = "";
        setPass("");
        kyLuc = 0;
    }
    NguoiChoi(std::string _id, std::string _name, std::string _pass, int _kyLuc);
    NguoiChoi(const NguoiChoi& other) {
        id = other.id;
        name = other.name;
        kyLuc = other.kyLuc;

    }
    ~NguoiChoi();

    int getKyLuc() const;
    void setKyLuc(int _kyLuc);

    friend std::ostream& operator<<(std::ostream& out, const NguoiChoi& nc);
    bool operator>(const NguoiChoi& other) const;
    void displayMenu() const override;
};