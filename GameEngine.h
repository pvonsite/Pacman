#pragma once

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class GameEngine {
    private:
        static SDL_Window* window;
        static SDL_Renderer* renderer;

        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
    public:
        static void initSDL();
        static void quitSDL();
};

#endif // _GAMEENGINE_H_
