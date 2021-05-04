#include "Object.h"
#include <iostream>
#include <cmath>

std::pair<int, int> nextTileID;

Object::Object(int tileX, int tileY, int velX, int velY) {
    this->tileX = tileX;
    this->tileY = tileY;
    if (velX != 0) this->velX = velX;
    if (velY != 0) this->velY = velY;

    this->scrPosX = tileX * 16 + 8;
    this->scrPosY = tileY * 16;
    dead = false;
}

bool Object::isDead() const {
    return dead;
}

int Object::getPosX() const {
    return scrPosX;
}

int Object::getPosY() const {
    return scrPosY;
}

int Object::getTileX() const {
    return tileX;
}

int Object::getTileY() const {
    return tileY;
}

void Object::reTilePos() {
    scrPosX = tileX * 16;
    scrPosY = tileY * 16;
}

void Object::changeVelocityDir(int velX, int velY, int dir) {
    this->velX = velX;
    this->velY = velY;
    this->dir = dir;
}

void Object::setDead(bool status) {
    dead = status;
    scrPosX = tileX * 16;
    scrPosY = tileY * 16;
}

void Object::move() {
    scrPosX += velX;
    scrPosY += velY;

    if (scrPosX % 16 == 0) tileX = scrPosX / 16;
    else tileX = (scrPosX + 8) / 16;

    if (scrPosY % 16 == 0) tileY = scrPosY / 16;
    else tileY = (scrPosY + 8) / 16;
}

void Object::goThroughTunnel() {
    if (scrPosY == 224) {
        if (dir == LEFT && scrPosX == 0) {
            tileX = 27;
            scrPosX = 432;
        }
        else if (dir == RIGHT && scrPosX == 432) {
            tileX = 0;
            scrPosX = 0;
        }
    }
}

void Object::resetObjectTile(const int tileX, const int tileY) {
    this->tileX = tileX;
    this->tileY = tileY;
    dead = false;
    velX = velY = 0;
    scrPosX = tileX * 16;
    scrPosY = tileY * 16;
}
