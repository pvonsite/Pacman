#pragma once

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Log.h"

class GameEngine {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const std::string Window_Tittle = "Pacman";
    public:
        GameEngine() {
            window = nullptr;
            renderer = nullptr;
        }
        ~GameEngine() {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            renderer = nullptr;
            window = nullptr;
        }
        void initSDL();
        void quitSDL();
};

#endif // _GAMEENGINE_H_
