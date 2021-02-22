#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <algorithm>

class Object {
    private:
        int scrPosX, scrPosY;
        int velX = 0, velY = 0;
        int tileX, tileY;
        int dir = 1;
    public:
        static const int UP = 1;
        static const int RIGHT = 2;
        static const int DOWN = 3;
        static const int LEFT = 4;
        static const int OBJECT_WIDTH  = 30;
        static const int OBJECT_HEIGHT = 30;
        static const int SCREEN_WIDTH = 448;
        static const int SCREEN_HEIGHT = 496;

        Object(int tileX, int tileY, int velX = 0, int velY = 0);

        void move();

        void stop();

        int getPosX() const {
            return this->scrPosX;
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

        int getOldDir() const {
            return dir % 2;
        }

        void changeVelocityDir(int velX, int velY, int dir) {
            this->velX = velX;
            this->velY = velY;
            this->dir = dir;
        }

        void changePos(int &newPosX, int &newPosY) {
            tileX = newPosX;
            tileY = newPosY;
        }
};

#endif // _OBJECT_H_
