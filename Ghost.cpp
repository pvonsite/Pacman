#include "Ghost.h"

Ghost::Ghost(int tileX, int tileY) : Object(tileX, tileY) {
    frighten = 0;
    scattering = false;
    ghostDir = LEFT;
    nextTileX = tileX, nextTileY = tileY;
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
