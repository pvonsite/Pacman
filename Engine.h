#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include "Map.h"
#include "TextureSrc.h"
#include "Pacman.h"
#include "Ghost.h"

class Engine {
    private:
        Map* map;
        Pacman* pacman;
        Ghost* blinky;
        Ghost* pinky;
        Ghost* inky;
        Ghost* clyde;
        TextureSrc* objectTexture;

        int pacmanFrame = 0;
        int ghostFrame = 0;
    public:
        Engine() {
            map = nullptr;
            pacman = nullptr;
            objectTexture = nullptr;
        }

        ~Engine() {
            map = nullptr;
            delete map;

            pacman = nullptr;
            delete pacman;

            objectTexture = nullptr;
            delete objectTexture;
        }

        void init(SDL_Renderer* &renderer);

        void handleEvent(SDL_Event &e);

        void render(SDL_Renderer* &renderer);

        void loop();

        void ghostMove(Ghost* &ghost);

        void pacmanMeatGhost(Ghost* &ghost);
};

#endif // _ENGINE_H_
