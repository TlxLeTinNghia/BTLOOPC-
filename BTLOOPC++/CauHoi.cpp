#include "CauHoi.h"

CauHoi::CauHoi(std::string chuDe, std::string capDo, std::string word, std::vector<std::string> goiY)
    : chuDe(chuDe), capDo(capDo), word(word), goiY(goiY) {
}

std::string CauHoi::getCapDo() const {
    return capDo;
}

std::string CauHoi::getChuDe() const {
    return chuDe;
}

std::vector<std::string> CauHoi::getGoiY() const {
    return goiY;
}

std::string CauHoi::getWord() const {
    return word;
}

std::string CauHoi::getCauHoi() const {
    if (goiY.empty()) return "Khong co goi y";
    return goiY[0];
}

std::istream& operator>>(std::istream& in, CauHoi& ch) {
    std::cout << "Nhap chu de: ";
    in >> std::ws;
    std::getline(in, ch.chuDe);

    std::cout << "Nhap cap do: ";
    std::getline(in, ch.capDo);

    std::cout << "Nhap dap an: ";
    std::getline(in, ch.word);

    int n;
    std::cout << "Nhap so goi y: ";
    in >> n;
    in.ignore();

    ch.goiY.clear();
    for (int i = 0; i < n; ++i) {
        std::string gy;
        std::cout << "Goi y " << i + 1 << ": ";
        std::getline(in, gy);
        ch.goiY.push_back(gy);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const CauHoi& ch) {
    out << "Chu de: " << ch.chuDe << '\n';
    out << "Cap do: " << ch.capDo << '\n';
    out << "Dap an: " << ch.word << '\n';
    out << "Goi y: ";
    for (const std::string& gy : ch.goiY) {
        out << gy << " | ";
    }
    out << '\n';
    return out;
}