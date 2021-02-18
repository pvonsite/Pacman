#pragma once

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Log.h"
#include "Texture.h"

class GameEngine {
    private:
        static SDL_Window* window;
        static SDL_Renderer* renderer;

        static bool Running;

        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
    public:

        static bool getRunStatus() {
            return Running;
        }

        static void initSDL();

        static void initTexture();

        static void quitSDL();

        static void handleEvent();
};

#endif // _GAMEENGINE_H_
