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
        bool inCage;
    public:
        static const int ghostVelocity = 2;
        static const int GHOST_START_TILE_X = 13;
        static const int GHOST_START_TILE_Y = 11;

        static const int DEFAULT_BLINKY_TILE_X = 27;
        static const int DEFAULT_BLINKY_TILE_Y = 1;
        static const int BLINKY_START_TILE_X = 13;
        static const int BLINKY_START_TILE_Y = 11;

        static const int DEFAULT_PINKY_TILE_X = 1;
        static const int DEFAULT_PINKY_TILE_Y = 1;
        static const int PINKY_START_TILE_X = 13;
        static const int PINKY_START_TILE_Y = 14;

        static const int DEFAULT_INKY_TILE_X = 27;
        static const int DEFAULT_INKY_TILE_Y = 30;
        static const int INKY_START_TILE_X = 11;
        static const int INKY_START_TILE_Y = 14;

        static const int DEFAULT_CLYDE_TILE_X = 1;
        static const int DEFAULT_CLYDE_TILE_Y = 30;
        static const int CLYDE_START_TILE_X = 15;
        static const int CLYDE_START_TILE_Y = 14;

        Ghost(int tileX, int tileY, bool inCage);

        int getNextTileX() const {
            return nextTileX;
        }

        int getNextTileY() const {
            return nextTileY;
        }

        int getGhostDir() const {
            return ghostDir;
        }

        void setDir(int dir) {
            ghostDir = dir;
        }

        void setFrighten(const bool status) {
            if (status) frighten = 500;
            else frighten = 0;
        }

        void setScattering(const bool status) {
            scattering = status;
        }

        bool isScattering() {
            return scattering;
        }

        bool isFrighten() {
            if (frighten > 0) --frighten;
            return (frighten > 0);
        }

        void setDestination(int tilX, int tilY);

        void moving();

        void respawn(const int tileX, const int tileY, const bool inCage);

        bool isInCage() const;
};

#endif // _GHOST_H_
