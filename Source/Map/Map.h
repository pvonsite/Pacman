#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "../Manager/LogStatus.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class Map {
    private:
        static const int MAP_WIDTH = 28;
        static const int MAP_HEIGHT = 31;
        const std::string mapFile = "Source/Map/map.txt";

        LogStatus* Console = new LogStatus("Map");

        int tile[MAP_HEIGHT][MAP_WIDTH];
        std::pair<int, int> nextCrossID[MAP_HEIGHT][MAP_WIDTH][4];
        bool markCross[MAP_HEIGHT][MAP_WIDTH][4];
    public:
        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;

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

        int eatCoins(const int &pacmanTileX, const int &pacmanTileY);

        void reset();
};

#endif // _MAP_H_
