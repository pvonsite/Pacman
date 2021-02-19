#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <string>
#include "Engine.h"

class Window {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Engine* engine = nullptr;

        bool Running = false;

        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        const std::string WINDOW_TITTLE = "Pacman";

    public:
        Window() {
            window = nullptr;
            renderer = nullptr;
            engine = nullptr;
        }

        ~Window() {
            engine = nullptr;

            if (renderer != nullptr) {
                SDL_DestroyRenderer(renderer);
                renderer = nullptr;
            }

            if (window != nullptr) {
                SDL_DestroyWindow(window);
                window = nullptr;
            }
        }

        void initSDL();

        void quitSDL();

        void runGame();

};

#endif // _WINDOW_H_
