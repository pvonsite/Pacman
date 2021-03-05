#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <algorithm>

class Object {
    private:
        int scrPosX, scrPosY;
        int velX = 0, velY = 0;
        int tileX, tileY;
        int dir;
        bool dead;
    public:
        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;
        static const int OBJECT_WIDTH  = 30;
        static const int OBJECT_HEIGHT = 30;
        static const int SCREEN_WIDTH = 448;
        static const int SCREEN_HEIGHT = 496;

        Object(int tileX, int tileY, int velX = 0, int velY = 0);

        void move();

        bool isDead() {
            return dead;
        }

        int getPosX() const {
            return scrPosX;
        }

        int getPosY() const {
            return scrPosY;
        }

        int getTileX() const {
            return tileX;
        }

        int getTileY() const {
            return tileY;
        }

        void changeVelocityDir(int velX, int velY, int dir) {
            this->velX = velX;
            this->velY = velY;
            this->dir = dir;
        }

        void setDead(bool status) {
            dead = status;
        }

        void resetPacmanTile() {
            tileX = 13; tileY = 23;
            velX = velY = 0;
            scrPosX = tileX * 16 + 8;
            scrPosY = tileY * 16;
            dead = false;
        }

        void goThroughTunnel();
};

#endif // _OBJECT_H_
