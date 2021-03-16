#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Engine.h"
#include "../Texture/Menu/Menu.h"

class Window {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Engine* engine = nullptr;
        Menu* menu = nullptr;

        LogStatus* Console = new LogStatus("Window");

        bool Running = false;
        bool runningMenu = true;
        bool runningEngine = false;

        static const int SCREEN_WIDTH = 882;
        static const int SCREEN_HEIGHT = 496;
        const std::string WINDOW_TITTLE = "Pacman";

    public:
        Window();

        ~Window();

        void initSDL();

        void quitSDL();

        void runGame();

};

#endif // _WINDOW_H_
