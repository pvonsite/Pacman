#pragma once

#ifndef _GHOST_H_
#define _GHOST_H_

#include "Object.h"
#include <iostream>

class Ghost : public Object {
    private:
        int nextTileX;
        int nextTileY;
        int frighten;
        int ghostDir;
        bool scattering;
    public:
        static const int ghostVelocity = 2;
        static const int DEFAULT_BLINKY_TILE_X = 27;
        static const int DEFAULT_BLINKY_TILE_Y = 1;
        static const int DEFAULT_PINKY_TILE_X = 1;
        static const int DEFAULT_PINKY_TILE_Y = 1;
        static const int DEFAULT_INKY_TILE_X = 27;
        static const int DEFAULT_INKY_TILE_Y = 30;
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
            if (status) frighten = 500;
            else frighten = 0;
        }

        void setScattering() {

        }

        bool isScattering() {
            return scattering;
        }

        bool isFrighten() {
            if (frighten > 0) --frighten;
            //std::cout << frighten<<std::endl;
            return (frighten > 0);
        }

        void setDestination(int tilX, int tilY);

        void moving();
};

#endif // _GHOST_H_
