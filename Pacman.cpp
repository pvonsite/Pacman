#include "Pacman.h"
#include <iostream>

Pacman::Pacman() : Object(13, 23) {
    eatenCoins = 0;
}

void Pacman::manageMove() {
    std::pair<int, int> nextTile = getNextTileID();

    if (abs(nextTile.first * 16 - getPosX()) <= 2 && abs(nextTile.second * 16 - getPosY()) <= 2) {
        changePos(nextTile.first, nextTile.second);
    }
}


