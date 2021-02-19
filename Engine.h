#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>

class Engine {
    public:
        Engine() {
            init();
        }

        void init();

        void handleEvent();

        void render(SDL_Renderer* &renderer);
};

#endif // _ENGINE_H_
