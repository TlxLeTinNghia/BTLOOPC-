#include "Game.h"
#include <iostream>

int Game::gameCounter = 0;

Game::Game() {
    ++gameCounter;
    diemSoGame = 0;
    HPNguoiChoi = 3;
    vongChoi = 1;
}

Game::~Game() {
}

int Game::goiY() {
    std::cout << "\n[He thong]: Ban da su dung quyen tro giup goi y!\n";
    return 1;
}