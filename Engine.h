#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include "Map.h"
#include "TextureSrc.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TickManager.h"

class Engine {
    private:
        Map* map;
        Pacman* pacman;
        Ghost* blinky;
        Ghost* pinky;
        Ghost* inky;
        Ghost* clyde;
        TextureSrc* objectTexture;
        TickManager* tickManager;
    public:
        Engine() {
            map = nullptr;
            pacman = nullptr;
            objectTexture = nullptr;
            tickManager = nullptr;
        }

        ~Engine() {
            map = nullptr;
            delete map;

            pacman = nullptr;
            delete pacman;

            objectTexture = nullptr;
            delete objectTexture;

            tickManager = nullptr;
            delete tickManager;
        }

        void revivalPacman();

        void resetTick() {
            tickManager->resetTick();
        }

        void init(SDL_Renderer* &renderer);

        void handleEvent(SDL_Event &e);

        void render(SDL_Renderer* &renderer);

        void loop();

        void ghostMove(Ghost* &ghost);

        void pacmanMeatGhost(Ghost* &ghost);

        void renderGhost(SDL_Renderer* &renderer, Ghost* &ghost, int ghostID);
};

#endif // _ENGINE_H_
