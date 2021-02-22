#include "Pacman.h"
#include <iostream>
#include <algorithm>

typedef std::pair<int, std::pair<int, int> > IP;

Pacman::Pacman() : Object(13, 23) {
    eatenCoins = 0;
}

void Pacman::pushtoStack(int newDir) {
    if (!Direction.empty()) Direction.pop();
    Direction.push(newDir);
}

void Pacman::pushSpecialStack(int newDir, std::pair<int, int> nextCross) {
    if (!Special.empty()) {
        if (Special.top().first != newDir) {
            Special.pop();
            Special.push( IP(newDir, nextCross) );
        }
    }
    else Special.push( IP(newDir,nextCross) );
}

void Pacman::moving() {
    if (!Direction.empty()) {
        int velX = 0, velY = 0, dir = 0;

        switch (Direction.top()) {
            case UP   : velX = 0; velY = -pacmanVelocity; dir = 1; break;
            case DOWN : velX = 0; velY =  pacmanVelocity; dir = 3; break;
            case LEFT : velX = -pacmanVelocity; velY = 0; dir = 4; break;
            case RIGHT: velX =  pacmanVelocity; velY = 0; dir = 2; break;
        }

        changeVelocityDir(velX, velY, dir);

        move();
    }
}

void Pacman::turn() {
    if (!Direction.empty()) stopmoving();
    Direction.push(Special.top().first);
    Special.pop();
    moving();
}

void Pacman::stopmoving() {
    while (!Direction.empty()) Direction.pop();
}

void Pacman::eraseSpecial() {
    while (!Special.empty()) Special.pop();
}
