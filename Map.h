#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "LogStatus.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class Map {
    private:
        static const int MAP_WIDTH = 28;
        static const int MAP_HEIGHT = 31;
        const std::string mapFile = "map.txt";

        LogStatus* Console = new LogStatus("Map");

        int tile[MAP_HEIGHT][MAP_WIDTH];
        std::pair<int, int> nextCrossID[MAP_HEIGHT][MAP_WIDTH][5];
        bool markCross[MAP_HEIGHT][MAP_WIDTH][5];
    public:
        static const int UP = 1;
        static const int RIGHT = 2;
        static const int DOWN = 3;
        static const int LEFT = 4;

        Map();

        ~Map() {
            Console = nullptr;
            delete Console;
        }

        int getTileID(int x, int y);

        std::pair<int, int> getnextCrossID(int x, int y, int dir);

        bool isWall(std::pair<int, int> tileID);

        bool iscrossRoad(int y, int x);

        bool canChangeDir(int x, int y, int newDir);

        bool besideCrossIsWall(std::pair<int, int> Cross, int newDir);

        void findingCrossRoad();

        void NextCrossTileID();

        bool eatCoins(int pacmanTileX, int pacmanTileY);
};

#endif // _MAP_H_
