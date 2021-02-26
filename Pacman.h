#pragma once

#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Object.h"
#include <stack>

class Pacman : public Object{
    private:
        int eatenCoins;
        bool dead;
        std::stack<int> Direction;
        std::stack< std::pair<int, std::pair<int, int> > > Special;

    public:
        static const int pacmanVelocity = 2;

        Pacman();

        ~Pacman() {
            eatenCoins = 0;
            dead = false;
        }

        bool isDead() const {
            return dead;
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
};

#endif // _PACMAN_H_
