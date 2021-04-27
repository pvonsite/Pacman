#pragma once

#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Object.h"
#include <stack>

class Pacman : public Object {
    private:
        std::stack<int> Direction;
        std::stack< std::pair<int, std::pair<int, int> > > Special;

    public:
        static const int pacmanVelocity = 2;
        static const int PACMAN_START_TILE_X = 13;
        static const int PACMAN_START_TILE_Y = 23;

        Pacman();

        ~Pacman() {
            while (!Direction.empty()) Direction.pop();
            while (!Special.empty()) Special.pop();
        }

        bool emptyDirStack() {
            return Direction.empty();
        }

        bool emptySpecial() {
            return Special.empty();
        }

        void pushtoStack(int newDir);

        void pushSpecialStack(int newDir, std::pair<int, int> nextCross);

        int getDir() const {
            return Direction.top();
        }

        std::pair<int, int> getSpecial() {
            return Special.top().second;
        }

        void moving();

        void stopmoving();

        void turn();

        void eraseSpecial();

        void respawn() {
            resetObjectTile(PACMAN_START_TILE_X, PACMAN_START_TILE_Y);
            while (!Direction.empty()) Direction.pop();
            while (!Special.empty())   Special.pop();
        }
};

#endif // _PACMAN_H_
