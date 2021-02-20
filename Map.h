#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "LogStatus.h"
#include <fstream>
#include <iostream>

class Map {
    private:
        static const int MAP_WIDTH = 28;
        static const int MAP_HEIGHT = 31;
        const std::string mapFile = "map.txt";

        LogStatus* Console = new LogStatus("Map");

        int tile[MAP_HEIGHT][MAP_WIDTH];
    public:
        Map();

        ~Map() {
            Console = nullptr;
            delete Console;
        }

        int getTileID(int x, int y);
};

#endif // _MAP_H_
