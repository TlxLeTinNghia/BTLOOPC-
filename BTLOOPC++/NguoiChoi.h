#pragma once
#include "NguoiDung.h"
#include <iostream>

class NguoiChoi : public NguoiDung {
private:
    int kyLuc;

public:
    NguoiChoi(std::string _id = "", std::string _name = "Unknown", std::string _pass = "123", int _kyLuc = 0);
    ~NguoiChoi();

    int getKyLuc() const;
    void setKyLuc(int _kyLuc);

    friend std::ostream& operator<<(std::ostream& out, const NguoiChoi& nc);
    bool operator>(const NguoiChoi& other) const;
    void displayMenu() const override;
};