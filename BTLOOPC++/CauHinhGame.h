#pragma once
#include <iostream>
using namespace std;

template <typename T>
class CauHinhGame {
private:
    T diemDe;
    T diemTrungBinh;
    T diemKho;
    T thoiGianMoiLuot;
    T soMangBanDau;

public:
    CauHinhGame(T _de = 10, T _tb = 20, T _kho = 30, T _time = 10, T _heart = 5)
        : diemDe(_de), diemTrungBinh(_tb), diemKho(_kho),
        thoiGianMoiLuot(_time), soMangBanDau(_heart) {
    }

    void setDiemDe(T x) { diemDe = x; }
    void setDiemTrungBinh(T x) { diemTrungBinh = x; }
    void setDiemKho(T x) { diemKho = x; }
    void setThoiGianMoiLuot(T x) { thoiGianMoiLuot = x; }
    void setSoMangBanDau(T x) { soMangBanDau = x; }

    T getDiemDe() const { return diemDe; }
    T getDiemTrungBinh() const { return diemTrungBinh; }
    T getDiemKho() const { return diemKho; }
    T getThoiGianMoiLuot() const { return thoiGianMoiLuot; }
    T getSoMangBanDau() const { return soMangBanDau; }

    template <typename U>
    friend ostream& operator<<(ostream& out, const CauHinhGame<U>& cfg);

    template <typename U>
    friend istream& operator>>(istream& in, CauHinhGame<U>& cfg);
};

template <typename T>
ostream& operator<<(ostream& out, const CauHinhGame<T>& cfg) {
    out << "===== GAME CONFIGURATION =====\n";
    out << "Easy points: " << cfg.diemDe << '\n';
    out << "Medium points: " << cfg.diemTrungBinh << '\n';
    out << "Hard points: " << cfg.diemKho << '\n';
    out << "Time each round: " << cfg.thoiGianMoiLuot << '\n';
    out << "Initial lives: " << cfg.soMangBanDau << '\n';
    return out;
}

template <typename T>
istream& operator>>(istream& in, CauHinhGame<T>& cfg) {
    cout << "Nhap diem de: "; in >> cfg.diemDe;
    cout << "Nhap diem trung binh: "; in >> cfg.diemTrungBinh;
    cout << "Nhap diem kho: "; in >> cfg.diemKho;
    cout << "Nhap thoi gian moi luot: "; in >> cfg.thoiGianMoiLuot;
    cout << "Nhap so mang ban dau: "; in >> cfg.soMangBanDau;
    return in;
}