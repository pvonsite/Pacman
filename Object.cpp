#include "Object.h"
#include <iostream>
#include <cmath>

std::pair<int, int> nextTileID;

Object::Object(int tileX, int tileY, int velX, int velY) {
    this->tileX = tileX;
    this->tileY = tileY;
    if (velX != 0) this->velX = velX;
    if (velY != 0) this->velY = velY;

    this->scrPosX = tileX * 16;
    this->scrPosY = tileY * 16;
}

void Object::move() {
    scrPosX += velX;
    scrPosY += velY;

    if (scrPosX % 16 == 0 && scrPosY % 16 == 0) {
        tileX = scrPosX / 16;
        tileY = scrPosY / 16;
    }
}

void Object::stop() {
    velX = 0; velY = 0;
    scrPosX = tileX * 16;
    scrPosY = tileY * 16;
}

std::pair<int, int> Object::getNextTileID(int tempDir) {
    if (tempDir == 0) tempDir = dir;
    nextTileID = {tileX, tileY};
    switch (tempDir) {
        case 1: nextTileID.second -= 1; break;
        case 2: nextTileID.first  += 1; break;
        case 3: nextTileID.second += 1; break;
        case 4: nextTileID.first  -= 1; break;
    }
    return nextTileID;
}
