#include "CauHinhGame.h"

CauHinhGame::CauHinhGame(int _de, int _tb, int _kho, int _time, int _heart)
    : diemDe(_de), diemTrungBinh(_tb), diemKho(_kho), thoiGianMoiLuot(_time), soMangBanDau(_heart) {
}

void CauHinhGame::setDiemDe(int x) { diemDe = x; }
void CauHinhGame::setDiemTrungBinh(int x) { diemTrungBinh = x; }
void CauHinhGame::setDiemKho(int x) { diemKho = x; }
void CauHinhGame::setThoiGianMoiLuot(int x) { thoiGianMoiLuot = x; }
void CauHinhGame::setSoMangBanDau(int x) { soMangBanDau = x; }

int CauHinhGame::getDiemDe() const { return diemDe; }
int CauHinhGame::getDiemTrungBinh() const { return diemTrungBinh; }
int CauHinhGame::getDiemKho() const { return diemKho; }
int CauHinhGame::getThoiGianMoiLuot() const { return thoiGianMoiLuot; }
int CauHinhGame::getSoMangBanDau() const { return soMangBanDau; }

std::ostream& operator<<(std::ostream& out, const CauHinhGame& cfg) {
    out << "===== GAME CONFIGURATION =====\n";
    out << "Easy points: " << cfg.diemDe << '\n';
    out << "Medium points: " << cfg.diemTrungBinh << '\n';
    out << "Hard points: " << cfg.diemKho << '\n';
    out << "Time each round: " << cfg.thoiGianMoiLuot << '\n';
    out << "Initial lives: " << cfg.soMangBanDau << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, CauHinhGame& cfg) {
    std::cout << "Nhap diem de: "; in >> cfg.diemDe;
    std::cout << "Nhap diem trung binh: "; in >> cfg.diemTrungBinh;
    std::cout << "Nhap diem kho: "; in >> cfg.diemKho;
    std::cout << "Nhap thoi gian moi luot: "; in >> cfg.thoiGianMoiLuot;
    std::cout << "Nhap so mang ban dau: "; in >> cfg.soMangBanDau;
    return in;
}