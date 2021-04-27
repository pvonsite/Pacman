#include "Ghost.h"
#include <random>
#include <iostream>

Ghost::Ghost(int tileX, int tileY, bool inCage) : Object(tileX, tileY) {
    frighten = 0;
    accele = 1;
    ghostVelocity = 2;
    scattering = false;
    nextTileX = tileX, nextTileY = tileY;
    this->inCage = inCage;
    if (inCage == false) ghostDir = RIGHT;
    else ghostDir = UP;
}

int Ghost::getNextTileX() const {
    return nextTileX;
}

int Ghost::getNextTileY() const {
    return nextTileY;
}

int Ghost::getGhostDir() const {
    return ghostDir;
}

void Ghost::setDir(int dir) {
    ghostDir = dir;
}

void Ghost::setFrighten(const bool status) {
    if (isInCage()) return;
    if (frighten != status) reTilePos();
    frighten = status;
    if (status) ghostDir = (ghostDir + 2) % 4;
}

void Ghost::setScattering(const bool status) {
    scattering = status;
}

bool Ghost::isScattering() {
    return scattering;
}

bool Ghost::isFrighten() {
    return frighten;
}

void Ghost::setDestination(int tilX, int tilY, int _accele) {
    this->accele = _accele;
    //std::cout << this->accele << std::endl;
    //if (accele != 1) resetObjectTile(this->getTileX(), this->getTileY());
    nextTileX = tilX;
    nextTileY = tilY;
}

void Ghost::moving() {
    int velX, velY, dir;
    velX = velY = 0; dir = -1;

    if (accele == 1) {
        if (frighten) ghostVelocity = 1;
        else if (isDead()) ghostVelocity = 4;
        else ghostVelocity = 2;
    }
    else ghostVelocity = 4;

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
