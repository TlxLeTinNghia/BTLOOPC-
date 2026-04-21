#include "HeThong.h"

HeThong::HeThong() : curentUser(nullptr) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
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

std::string HeThong::trim(const std::string& s) {
    std::size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    std::size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string HeThong::chuanHoaMucDo(const std::string& mucDo) const {
    std::string temp = mucDo;
    for (char& c : temp) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (temp == "easy" || temp == "de") return "Easy";
    if (temp == "medium" || temp == "trungbinh" || temp == "trung_binh") return "Medium";
    if (temp == "hard" || temp == "kho") return "Hard";
    return "";
}

int HeThong::demKyTuCoTheDoan(const std::string& word) const {
    int dem = 0;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            ++dem;
        }
    }
    return dem;
}

int HeThong::demKyTuCanChe(const std::string& word, const std::string& mucDo) const {
    int tongKyTu = demKyTuCoTheDoan(word);
    if (tongKyTu <= 1) return tongKyTu;

    if (mucDo == "Easy") {
        return std::max(1, tongKyTu * 5 / 10);
    }
    if (mucDo == "Medium") {
        return std::max(1, tongKyTu * 7 / 10);
    }
    if (mucDo == "Hard") {
        return std::max(1, tongKyTu * 9 / 10);
    }
    return tongKyTu;
}

std::string HeThong::taoTuBiChe(const std::string& word, const std::string& mucDo) const {
    std::string display = word;
    std::vector<int> viTriCoTheChe;

    for (int i = 0; i < static_cast<int>(word.size()); ++i) {
        if (std::isalnum(static_cast<unsigned char>(word[i]))) {
            viTriCoTheChe.push_back(i);
        }
    }

    int soKyTuCanChe = demKyTuCanChe(word, mucDo);
    if (soKyTuCanChe <= 0 || viTriCoTheChe.empty()) {
        return display;
    }

    int soDaChe = 0;
    while (soDaChe < soKyTuCanChe && !viTriCoTheChe.empty()) {
        int indexNgauNhien = std::rand() % viTriCoTheChe.size();
        int viTri = viTriCoTheChe[indexNgauNhien];
        display[viTri] = '_';
        viTriCoTheChe.erase(viTriCoTheChe.begin() + indexNgauNhien);
        ++soDaChe;
    }

    return display;
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

void HeThong::loadQuestion(std::unordered_map<std::string, std::vector<CauHoi>>& _listQuestion) {
    std::ifstream fin("ListQuestion.txt");
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 3) continue;

        std::string chuDe = tokens[0];
        std::string word;
        std::vector<std::string> goiY;

        std::string mucDoCu = chuanHoaMucDo(tokens[1]);
        if (!mucDoCu.empty() && tokens.size() >= 4) {
            word = tokens[2];
            for (std::size_t i = 3; i < tokens.size(); ++i) {
                if (!tokens[i].empty()) goiY.push_back(tokens[i]);
            }
        }
        else {
            word = tokens[1];
            for (std::size_t i = 2; i < tokens.size(); ++i) {
                if (!tokens[i].empty()) goiY.push_back(tokens[i]);
            }
        }

        if (!chuDe.empty() && !word.empty()) {
            _listQuestion[chuDe].push_back(CauHoi(chuDe, word, goiY));
        }
    }
}

void HeThong::unloadQuestion() {
    std::ofstream fout("ListQuestion.txt");
    for (const auto& x : listQuestion) {
        for (const CauHoi& z : x.second) {
            fout << x.first << ',' << z.getWord();
            for (const std::string& gy : z.getGoiY()) {
                fout << ',' << gy;
            }
            fout << '\n';
        }
    }
}

CauHinhGame<int> HeThong::loadConfig() {
    std::ifstream fin("ConfigGame.txt");
    std::string line;
    if (!std::getline(fin, line)) {
        return CauHinhGame<int>();
    }

    std::stringstream ss(line);
    std::string diemDe, diemTB, diemKho, time, lives;
    std::getline(ss, diemDe, ',');
    std::getline(ss, diemTB, ',');
    std::getline(ss, diemKho, ',');
    std::getline(ss, time, ',');
    std::getline(ss, lives, ',');

    return CauHinhGame<int>(std::stoi(diemDe), std::stoi(diemTB), std::stoi(diemKho), std::stoi(time), std::stoi(lives));
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

    std::cout << "Moi tu trong chu de " << chuDe << " deu choi duoc 3 muc:\n";
    std::cout << "- Easy   : hien san nhieu chu cai hon\n";
    std::cout << "- Medium : hien san it chu cai hon\n";
    std::cout << "- Hard   : an toi da ky tu\n";
}

void HeThong::batDauTroChoi(const CauHinhGame<int>& cfg, const std::string& chuDe, const std::string& mucDoNhap , const int& _heart,const int& _score) {
    auto topicIt = listQuestion.find(chuDe);
    if (topicIt == listQuestion.end() || topicIt->second.empty()) {
        std::cout << "Khong co chu de nay.\n";
        return;
    }

    std::string mucDo = chuanHoaMucDo(mucDoNhap);
    if (mucDo.empty()) {
        std::cout << "Muc do khong hop le. Vui long nhap Easy / Medium / Hard.\n";
        return;
    }

    const std::vector<CauHoi>& ds = topicIt->second;
    const CauHoi& q = ds[std::rand() % ds.size()];

    std::string target = q.getWord();
    std::string display = taoTuBiChe(target, mucDo);
    std::vector<std::string> goiY = q.getGoiY();

    int lives = _heart;
    int score = _score;
    int soGoiYDangMo = goiY.empty() ? 0 : 1;
    historyGame.clear();

    while (lives > 0 && display != target) {
        std::cout << "\nTu can doan: " << display << '\n';
        std::cout << "So mang con lai: " << lives << '\n';
        std::cout << "Muc do hien tai: " << mucDo << '\n';

        if (soGoiYDangMo == 0) {
            std::cout << "Goi y: Khong co goi y nao.\n";
        }
        else {
            std::cout << "Goi y dang mo:\n";
            for (int i = 0; i < soGoiYDangMo; ++i) {
                std::cout << "  " << i + 1 << ". " << goiY[i] << '\n';
            }
        }

        if (!goiY.empty()) {
            std::cout << "So goi y da mo: " << soGoiYDangMo << '/' << goiY.size() << '\n';
            if (soGoiYDangMo < static_cast<int>(goiY.size())) {
                std::cout << "Nhap phim 1 de mo them goi y tiep theo.\n";
            }
            else {
                std::cout << "Ban da dung het goi y.\n";
            }
        }

        if (!historyGame.empty()) {
            std::cout << "Da doan: ";
            for (const std::string& s : historyGame) {
                std::cout << s << ' ';
            }
            std::cout << '\n';
        }

        std::string luaChon;
        std::cout << "Nhap 1 ky tu de doan (hoac nhap 1 de xem them goi y): ";
        std::cin >> luaChon;

        if (luaChon == "1") {
            if (soGoiYDangMo < static_cast<int>(goiY.size())) {
                ++soGoiYDangMo;
                std::cout << "Da mo them goi y moi.\n";
            }
            else {
                std::cout << "Khong con goi y nao de mo them.\n";
            }
            continue;
        }

        if (luaChon.size() != 1) {
            std::cout << "Chi duoc nhap 1 ky tu hoac phim 1 de xem goi y.\n";
            continue;
        }

        char guessLower = static_cast<char>(std::tolower(static_cast<unsigned char>(luaChon[0])));
        bool daDoan = false;
        for (const std::string& s : historyGame) {
            if (!s.empty() && s[0] == guessLower) {
                daDoan = true;
                break;
            }
        }

        if (daDoan) {
            std::cout << "Ban da doan ky tu nay roi. Hay nhap ky tu khac.\n";
            continue;
        }

        historyGame.push_back(std::string(1, guessLower));

        bool found = false;
        for (std::size_t i = 0; i < target.size(); ++i) {
            if (display[i] == '_' &&
                std::tolower(static_cast<unsigned char>(target[i])) == guessLower) {
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
    if (lives == 0) {
        NguoiChoi* p = dynamic_cast<NguoiChoi*>(curentUser);
        if (p) {
            p->setKyLuc(score);
            std::cout << "Ban nhan duoc " << score << " diem.\n";
        }
    }
    if (display == target) {
        std::cout << "\nChuc mung! Ban da doan dung tu: " << target << '\n';
        if (mucDo == "Easy") score += cfg.getDiemDe();
        else if (mucDo == "Medium") score += cfg.getDiemTrungBinh();
        else score += cfg.getDiemKho();

        batDauTroChoi(cfg, chuDe, mucDo , lives,score);
    }
    else {
        std::cout << "\nGame Over! Tu dung la: " << target << '\n';
    }

    historyGame.clear();
}

void HeThong::addQuestion() {
    CauHoi moi;
    std::cin >> moi;

    listQuestion[moi.getChuDe()].push_back(moi);

    std::cout << "Them cau hoi thanh cong vao chu de ["
        << moi.getChuDe() << "].\n";
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
            std::cout << "Nhap muc do (Easy / Medium / Hard): ";
            std::cin >> mucDo;
            batDauTroChoi(config, chuDe, mucDo , config.getSoMangBanDau());
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
        const std::vector<CauHoi>& ds = chuDePair.second;
        for (std::size_t i = 0; i < ds.size(); ++i) {
            std::cout << "    [" << i << "] " << ds[i];
        }
    }
}

void HeThong::editQuestion() {
    std::string chuDe;
    std::cout << "Nhap chu de can sua: ";
    std::cin >> chuDe;

    auto itChuDe = listQuestion.find(chuDe);
    if (itChuDe == listQuestion.end() || itChuDe->second.empty()) {
        std::cout << "Khong tim thay chu de.\n";
        return;
    }

    std::vector<CauHoi>& ds = itChuDe->second;

    for (std::size_t i = 0; i < ds.size(); ++i) {
        std::cout << "\n[" << i << "]\n";
        std::cout << ds[i];
    }

    int index;
    std::cout << "Nhap chi so cau hoi can sua: ";
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
    std::string chuDe;
    std::cout << "Nhap chu de can xoa: ";
    std::cin >> chuDe;

    auto itChuDe = listQuestion.find(chuDe);
    if (itChuDe == listQuestion.end() || itChuDe->second.empty()) {
        std::cout << "Khong tim thay chu de.\n";
        return;
    }

    std::vector<CauHoi>& ds = itChuDe->second;

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