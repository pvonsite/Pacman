#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include "Map.h"
#include "TextureSrc.h"

class Engine {
    private:
        Map* map;
        TextureSrc* objectTexture;
    public:
        Engine() {
            map = nullptr;
            objectTexture = nullptr;
        }

        ~Engine() {
            map = nullptr;
            delete map;
            objectTexture = nullptr;
            delete objectTexture;
        }

        void init(SDL_Renderer* &renderer);

        void handleEvent(SDL_Event &e);

        void render(SDL_Renderer* &renderer);
};

#endif // _ENGINE_H_
