#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "NguoiChoi.h"
#include "Admin.h"
#include "CauHoi.h"
#include "CauHinhGame.h"

class HeThong {
private:
    CauHinhGame config;
    std::map<std::string, NguoiDung*> listPlayer;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<CauHoi>>> listQuestion;
    std::vector<std::string> historyGame;
    NguoiDung* curentUser;

public:
    HeThong();
    ~HeThong();

    bool Login(const std::string& user, const std::string& pass);
    void Logout();
    void run();
    void batDauTroChoi(const CauHinhGame& cfg, const std::string& chuDe, const std::string& mucDo);

    void readFileUser();
    void writeFileUser();
    void loadQuestion(std::unordered_map<std::string, std::unordered_map<std::string, std::vector<CauHoi>>>& _listQuestion);
    void unloadQuestion();
    CauHinhGame loadConfig();
    void unloadConfig();
    void showTopics() const;
    void showLevels(const std::string& chuDe) const;
    void menuAdmin();
    void menuNguoiChoi();

    void addQuestion();
    void editQuestion();
    void deleteQuestion();
    void showAllQuestions() const;
};