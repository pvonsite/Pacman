#pragma once

#ifndef _GHOST_H_
#define _GHOST_H_

#include "Object.h"

class Ghost : public Object {
    private:
        int nextTileX;
        int nextTileY;
        int frighten;
        int ghostDir;
        bool dead;
    public:
        static const int ghostVelocity = 2;
        static const int DEFAULT_CLYDE_TILE_X = 1;
        static const int DEFAULT_CLYDE_TILE_Y = 30;

        Ghost(int tileX, int tileY);

        int getNextTileX()  {
            return nextTileX;
        }

        int getNextTileY()  {
            return nextTileY;
        }

        int getGhostDir() {
            return ghostDir;
        }

        void setDir(int dir) {
            ghostDir = dir;
        }

        void setFrighten( bool status) {
            if (status) frighten = 5000;
            else frighten = 0;
        }

        bool isFrighten() {
            if (frighten > 0) --frighten;
            return (frighten > 0);
        }

        void setDestination(int tilX, int tilY);

        void moving();
};

#endif // _GHOST_H_
