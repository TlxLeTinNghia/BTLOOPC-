#pragma once
#include <iostream>

class Game {
protected:
    int diemSoGame;
    int HPNguoiChoi;
    int vongChoi;
    static int gameCounter;

public:
    Game();
    ~Game();
    int goiY();
};