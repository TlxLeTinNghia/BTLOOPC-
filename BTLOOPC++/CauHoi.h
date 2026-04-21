#pragma once
#include <string>
#include <vector>
#include <iostream>

class CauHoi {
private:
    std::string chuDe;
    std::string word;
    std::vector<std::string> goiY;

public:
    CauHoi(std::string chuDe = "", std::string word = "", std::vector<std::string> goiY = {});

    std::string getChuDe() const;
    std::vector<std::string> getGoiY() const;
    std::string getWord() const;
    std::string getCauHoi() const;

    friend std::istream& operator>>(std::istream& in, CauHoi& ch);
    friend std::ostream& operator<<(std::ostream& out, const CauHoi& ch);
};