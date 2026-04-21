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