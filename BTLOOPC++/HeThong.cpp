#include "HeThong.h"

HeThong::HeThong() : curentUser(nullptr) {
    readFileUser();
    loadQuestion(listQuestion);
    config = loadConfig();
}

HeThong::~HeThong() {
    writeFileUser();
    unloadQuestion();
    unloadConfig();

    for (auto& item : listPlayer) {
        delete item.second;
    }
    listPlayer.clear();
}

bool HeThong::Login(const std::string& user, const std::string& pass) {
    auto it = listPlayer.find(user);
    if (it != listPlayer.end() && it->second->getPass() == pass) {
        curentUser = it->second;
        return true;
    }
    return false;
}

void HeThong::Logout() {
    curentUser = nullptr;
}

void HeThong::readFileUser() {
    std::ifstream fin("ListUser.txt");
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name, pass, scoreStr, roleStr;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, pass, ',');
        std::getline(ss, scoreStr, ',');
        std::getline(ss, roleStr, ',');

        int score = 0;
        if (!scoreStr.empty()) score = std::stoi(scoreStr);

        if (roleStr == "Admin") {
            Admin* ad = new Admin(id, name, pass);
            ad->setRole("Admin");
            listPlayer[name] = ad;
        }
        else {
            NguoiChoi* p = new NguoiChoi(id, name, pass, score);
            p->setRole("Player");
            listPlayer[name] = p;
        }
    }
}

void HeThong::writeFileUser() {
    std::ofstream fout("ListUser.txt");
    for (const auto& item : listPlayer) {
        const NguoiDung* ptr = item.second;
        const NguoiChoi* p = dynamic_cast<const NguoiChoi*>(ptr);
        int score = p ? p->getKyLuc() : 0;
        fout << ptr->getId() << ','
            << ptr->getName() << ','
            << ptr->getPass() << ','
            << score << ','
            << ptr->getRole() << '\n';
    }
}

void HeThong::loadQuestion(std::unordered_map<std::string, std::unordered_map<std::string, std::vector<CauHoi>>>& _listQuestion) {
    std::ifstream fin("ListQuestion.txt");
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string chuDe, mucDo, word;
        std::vector<std::string> goiY;

        std::getline(ss, chuDe, ',');
        std::getline(ss, mucDo, ',');
        std::getline(ss, word, ',');

        std::string gy;
        while (std::getline(ss, gy, ',')) {
            goiY.push_back(gy);
        }

        _listQuestion[chuDe][mucDo].push_back(CauHoi(chuDe, mucDo, word, goiY));
    }
}

void HeThong::unloadQuestion() {
    std::ofstream fout("ListQuestion.txt");
    for (const auto& x : listQuestion) {
        for (const auto& y : x.second) {
            for (const CauHoi& z : y.second) {
                fout << x.first << ',' << y.first << ',' << z.getWord();
                for (const std::string& gy : z.getGoiY()) {
                    fout << ',' << gy;
                }
                fout << '\n';
            }
        }
    }
}

CauHinhGame HeThong::loadConfig() {
    std::ifstream fin("ConfigGame.txt");
    std::string line;
    if (!std::getline(fin, line)) {
        return CauHinhGame();
    }

    std::stringstream ss(line);
    std::string diemDe, diemTB, diemKho, time, lives;
    std::getline(ss, diemDe, ',');
    std::getline(ss, diemTB, ',');
    std::getline(ss, diemKho, ',');
    std::getline(ss, time, ',');
    std::getline(ss, lives, ',');

    return CauHinhGame(std::stoi(diemDe), std::stoi(diemTB), std::stoi(diemKho), std::stoi(time), std::stoi(lives));
}

void HeThong::unloadConfig() {
    std::ofstream fout("ConfigGame.txt");
    fout << config.getDiemDe() << ','
        << config.getDiemTrungBinh() << ','
        << config.getDiemKho() << ','
        << config.getThoiGianMoiLuot() << ','
        << config.getSoMangBanDau();
}

void HeThong::showTopics() const {
    std::cout << "Chu de hien co:\n";
    for (const auto& item : listQuestion) {
        std::cout << "- " << item.first << '\n';
    }
}

void HeThong::showLevels(const std::string& chuDe) const {
    auto it = listQuestion.find(chuDe);
    if (it == listQuestion.end()) {
        std::cout << "Khong ton tai chu de nay.\n";
        return;
    }

    std::cout << "Cap do hien co trong chu de " << chuDe << ":\n";
    for (const auto& item : it->second) {
        std::cout << "- " << item.first << '\n';
    }
}

void HeThong::batDauTroChoi(const CauHinhGame& cfg, const std::string& chuDe, const std::string& mucDo) {
    auto topicIt = listQuestion.find(chuDe);
    if (topicIt == listQuestion.end()) {
        std::cout << "Khong co chu de nay.\n";
        return;
    }

    auto levelIt = topicIt->second.find(mucDo);
    if (levelIt == topicIt->second.end() || levelIt->second.empty()) {
        std::cout << "Khong co cau hoi o muc do nay.\n";
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    const std::vector<CauHoi>& ds = levelIt->second;
    const CauHoi& q = ds[std::rand() % ds.size()];

    std::string target = q.getWord();
    std::string display(target.size(), '_');
    int lives = cfg.getSoMangBanDau();
    int score = 0;

    while (lives > 0 && display != target) {
        std::cout << "\nTu can doan: " << display << '\n';
        std::cout << "So mang con lai: " << lives << '\n';
        std::cout << "Goi y:\n";
        std::vector<std::string> goiY = q.getGoiY();
        for (std::size_t i = 0; i < goiY.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << goiY[i] << '\n';
        }

        char guess;
        std::cout << "Nhap 1 ki tu: ";
        std::cin >> guess;

        historyGame.push_back(std::string(1, guess));

        bool found = false;
        for (std::size_t i = 0; i < target.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(target[i])) == std::tolower(static_cast<unsigned char>(guess))) {
                display[i] = target[i];
                found = true;
            }
        }

        if (!found) {
            --lives;
            std::cout << "Sai roi!\n";
        }
        else {
            std::cout << "Dung roi!\n";
        }
    }

    if (display == target) {
        std::cout << "\nChuc mung! Ban da doan dung tu: " << target << '\n';
        if (mucDo == "Easy") score = cfg.getDiemDe();
        else if (mucDo == "Medium") score = cfg.getDiemTrungBinh();
        else score = cfg.getDiemKho();

        NguoiChoi* p = dynamic_cast<NguoiChoi*>(curentUser);
        if (p) {
            p->setKyLuc(score);
            std::cout << "Ban nhan duoc " << score << " diem.\n";
        }
    }
    else {
        std::cout << "\nGame Over! Tu dung la: " << target << '\n';
    }

    historyGame.clear();
}

void HeThong::addQuestion() {
    CauHoi moi;
    std::cin >> moi;

    listQuestion[moi.getChuDe()][moi.getCapDo()].push_back(moi);

    std::cout << "Them cau hoi thanh cong vao chu de ["
        << moi.getChuDe() << "] muc do ["
        << moi.getCapDo() << "].\n";
}


void HeThong::run() {
    while (true) {
        std::string tk, mk;
        std::cout << "===== DANG NHAP =====\n";
        std::cout << "Tai khoan: ";
        std::cin >> tk;
        std::cout << "Mat khau: ";
        std::cin >> mk;

        if (Login(tk, mk)) {
            std::cout << "Dang nhap thanh cong. Xin chao " << curentUser->getName() << "\n";

            if (dynamic_cast<Admin*>(curentUser)) {
                menuAdmin();
            }
            else {
                menuNguoiChoi();
            }
        }
        else {
            std::system("cls");
            std::cout << "Sai tai khoan hoac mat khau.\n";
        }

        int tiep;
        std::cout << "Nhap 1 de dang nhap tiep, 0 de thoat: ";
        std::cin >> tiep;
        if (tiep == 0) break;
    }
}
void HeThong::menuAdmin() {
    int choice;

    do {
        curentUser->displayMenu();
        std::cout << "Lua chon: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addQuestion();
            break;
        case 2:
            editQuestion();
            break;
        case 3:
            deleteQuestion();
            break;
        case 4:
            showAllQuestions();
            break;
        case 5:
            std::cout << config;
            break;
        case 6:
            Logout();
            std::cout << "Da dang xuat.\n";
            return;
        default:
            std::cout << "Lua chon khong hop le.\n";
        }

    } while (true);
}

void HeThong::menuNguoiChoi() {
    int choice;
    do {
        curentUser->displayMenu();
        std::cout << "Lua chon: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string chuDe, mucDo;
            showTopics();
            std::cout << "Nhap chu de: ";
            std::cin >> chuDe;
            showLevels(chuDe);
            std::cout << "Nhap muc do: ";
            std::cin >> mucDo;
            batDauTroChoi(config, chuDe, mucDo);
            break;
        }
        case 2: {
            NguoiChoi* p = dynamic_cast<NguoiChoi*>(curentUser);
            if (p) {
                std::cout << "Ky luc cua ban: " << p->getKyLuc() << '\n';
            }
            break;
        }
        case 3:
            Logout();
            std::cout << "Da dang xuat.\n";
            return;
        case 0:
            return;
        default:
            std::cout << "Lua chon khong hop le.\n";
        }
    } while (true);
}

void HeThong::showAllQuestions() const {
    for (const auto& chuDePair : listQuestion) {
        std::cout << "\nChu de: " << chuDePair.first << '\n';

        for (const auto& mucDoPair : chuDePair.second) {
            std::cout << "  Muc do: " << mucDoPair.first << '\n';

            const std::vector<CauHoi>& ds = mucDoPair.second;
            for (std::size_t i = 0; i < ds.size(); ++i) {
                std::cout << "    [" << i << "] " << ds[i];
            }
        }
    }
}
void HeThong::editQuestion() {
    std::string chuDe, mucDo;
    std::cout << "Nhap chu de can sua: ";
    std::cin >> chuDe;
    std::cout << "Nhap muc do can sua: ";
    std::cin >> mucDo;

    auto itChuDe = listQuestion.find(chuDe);
    if (itChuDe == listQuestion.end()) {
        std::cout << "Khong tim thay chu de.\n";
        return;
    }

    auto itMucDo = itChuDe->second.find(mucDo);
    if (itMucDo == itChuDe->second.end() || itMucDo->second.empty()) {
        std::cout << "Khong tim thay cau hoi o muc do nay.\n";
        return;
    }

    std::vector<CauHoi>& ds = itMucDo->second;

    for (std::size_t i = 0; i < ds.size(); ++i) {
        std::cout << "\n[" << i << "]\n";
        std::cout << ds[i];
    }

    int index;
    std::cout << "Nhap chi so cau hoi can sua: ";
    std::cin >> index;
    std::cin.ignore();

    if (index < 0 || index >= static_cast<int>(ds.size())) {
        std::cout << "Chi so khong hop le.\n";
        return;
    }

    std::cout << "Nhap lai thong tin cau hoi moi:\n";
    CauHoi moi;
    std::cin >> moi;

    ds[index] = moi;
    std::cout << "Sua cau hoi thanh cong.\n";
}
void HeThong::deleteQuestion() {
    std::string chuDe, mucDo;
    std::cout << "Nhap chu de can xoa: ";
    std::cin >> chuDe;
    std::cout << "Nhap muc do can xoa: ";
    std::cin >> mucDo;

    auto itChuDe = listQuestion.find(chuDe);
    if (itChuDe == listQuestion.end()) {
        std::cout << "Khong tim thay chu de.\n";
        return;
    }

    auto itMucDo = itChuDe->second.find(mucDo);
    if (itMucDo == itChuDe->second.end() || itMucDo->second.empty()) {
        std::cout << "Khong tim thay cau hoi o muc do nay.\n";
        return;
    }

    std::vector<CauHoi>& ds = itMucDo->second;

    for (std::size_t i = 0; i < ds.size(); ++i) {
        std::cout << "\n[" << i << "]\n";
        std::cout << ds[i];
    }

    int index;
    std::cout << "Nhap chi so cau hoi can xoa: ";
    std::cin >> index;

    if (index < 0 || index >= static_cast<int>(ds.size())) {
        std::cout << "Chi so khong hop le.\n";
        return;
    }

    ds.erase(ds.begin() + index);
    std::cout << "Xoa cau hoi thanh cong.\n";
}