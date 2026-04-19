#pragma once
#include <iostream>

class CauHinhGame {
private:
    int diemDe;
    int diemTrungBinh;
    int diemKho;
    int thoiGianMoiLuot;
    int soMangBanDau;

public:
    CauHinhGame(int _de = 10, int _tb = 20, int _kho = 30, int _time = 10, int _heart = 5);

    void setDiemDe(int x);
    void setDiemTrungBinh(int x);
    void setDiemKho(int x);
    void setThoiGianMoiLuot(int x);
    void setSoMangBanDau(int x);

    int getDiemDe() const;
    int getDiemTrungBinh() const;
    int getDiemKho() const;
    int getThoiGianMoiLuot() const;
    int getSoMangBanDau() const;

    friend std::ostream& operator<<(std::ostream& out, const CauHinhGame& cfg);
    friend std::istream& operator>>(std::istream& in, CauHinhGame& cfg);
};







