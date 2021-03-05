#pragma once

#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Object.h"
#include <stack>

class Pacman : public Object {
    private:
        int lifes;
        int eatenCoins = 0;
        std::stack<int> Direction;
        std::stack< std::pair<int, std::pair<int, int> > > Special;

    public:
        static const int pacmanVelocity = 2;

        Pacman();

        ~Pacman() {
            lifes = 0;
            eatenCoins = 0;
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

        void eatCoins() {
            ++eatenCoins;
        }

        bool getLife() {
            if (lifes > 0) --lifes;
            return (lifes > 0);
        }

        void respawn() {
            resetPacmanTile();
            while (!Direction.empty()) Direction.pop();
            while (!Special.empty())   Special.pop();
        }
};

#endif // _PACMAN_H_
