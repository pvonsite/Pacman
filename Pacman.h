#pragma once

#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Object.h"
#include <SDL.h>

class Pacman : public Object{
    private:
        int eatenCoins;
    public:
        static const int pacmanVelocity = 2;

        Pacman();

        ~Pacman() {
            eatenCoins = 0;
        }

        void manageMove();

        void handleEvent(SDL_Event &e);
};

#endif // _PACMAN_H_
