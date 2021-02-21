#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include "Map.h"
#include "TextureSrc.h"
#include "Pacman.h"

class Engine {
    private:
        Map* map;
        Pacman* pacman;
        TextureSrc* objectTexture;
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

        bool pacmanCanMove();
};

#endif // _ENGINE_H_
