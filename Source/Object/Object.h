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

        ~Object() {

        }

        void move();

        bool isDead() const;

        int getPosX() const;

        int getPosY() const;

        int getTileX() const;

        int getTileY() const;

        void reTilePos();

        void changeVelocityDir(int velX, int velY, int dir);

        void setDead(bool status, int id = 0);

        void resetObjectTile(const int tileX, const int tileY);

        void goThroughTunnel();
};

#endif // _OBJECT_H_
