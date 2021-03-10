#include "Ghost.h"
#include <random>

Ghost::Ghost(int tileX, int tileY, bool inCage) : Object(tileX, tileY) {
    frighten = 0;
    scattering = false;
    nextTileX = tileX, nextTileY = tileY;
    this->inCage = inCage;
    if (inCage == false) ghostDir = RIGHT;
    else ghostDir = UP;
}

void Ghost::setDestination(int tilX, int tilY) {
    nextTileX = tilX;
    nextTileY = tilY;
}

void Ghost::moving() {
    int velX, velY, dir;
    velX = velY = 0; dir = -1;

    switch (ghostDir) {
        case UP:    velY -= ghostVelocity; dir = UP;    break;
        case DOWN:  velY += ghostVelocity; dir = DOWN;  break;
        case LEFT:  velX -= ghostVelocity; dir = LEFT;  break;
        case RIGHT: velX += ghostVelocity; dir = RIGHT; break;
    }
    changeVelocityDir(velX, velY, dir);
    move();
}

void Ghost::respawn(const int tileX, const int tileY, const bool inCage) {
    resetObjectTile(tileX, tileY);
    this->inCage = inCage;
    if (inCage == false) {
        if (rand() % 2 == 0) ghostDir = LEFT;
        else ghostDir = RIGHT;
    }
    else ghostDir = UP;
}

bool Ghost::isInCage() const {
    return inCage;
}
