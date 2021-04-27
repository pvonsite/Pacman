#pragma once

#ifndef _GHOST_H_
#define _GHOST_H_

#include "Object.h"
#include <iostream>

class Ghost : public Object {
    private:
        int nextTileX;
        int nextTileY;
        int ghostDir;
        bool frighten;
        bool scattering;
        bool inCage;
        int ghostVelocity;
        int accele;
    public:
        static const int GHOST_START_TILE_X = 13;
        static const int GHOST_START_TILE_Y = 11;

        static const int DEFAULT_BLINKY_TILE_X = 26;
        static const int DEFAULT_BLINKY_TILE_Y = 1;
        static const int BLINKY_START_TILE_X = 13;
        static const int BLINKY_START_TILE_Y = 11;

        static const int DEFAULT_PINKY_TILE_X = 1;
        static const int DEFAULT_PINKY_TILE_Y = 1;
        static const int PINKY_START_TILE_X = 13;
        static const int PINKY_START_TILE_Y = 14;

        static const int DEFAULT_INKY_TILE_X = 26;
        static const int DEFAULT_INKY_TILE_Y = 29;
        static const int INKY_START_TILE_X = 11;
        static const int INKY_START_TILE_Y = 14;

        static const int DEFAULT_CLYDE_TILE_X = 1;
        static const int DEFAULT_CLYDE_TILE_Y = 29;
        static const int CLYDE_START_TILE_X = 15;
        static const int CLYDE_START_TILE_Y = 14;

        Ghost(int tileX, int tileY, bool inCage);

        int getNextTileX() const;

        int getNextTileY() const;

        int getGhostDir() const;

        void setDir(int dir);

        void setFrighten(const bool status);

        void setScattering(const bool status);

        bool isScattering();

        bool isFrighten();

        void setDestination(int tilX, int tilY, int _accele = 1);

        void moving();

        void respawn(const int tileX, const int tileY, const bool inCage);

        bool isInCage() const;
};

#endif // _GHOST_H_
