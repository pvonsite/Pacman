#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "PlayStateManager.h"
#include "../Menu/Button.h"

class Window {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Menu* startMenu = nullptr;
        PlayStateManager* playState = nullptr;

        LogStatus* Console = new LogStatus("Window");
        std::vector<std::string> highScore;
        bool Running = false;
        bool runningMenu = false;
    public:
        static const int SCREEN_WIDTH = 882;
        static const int SCREEN_HEIGHT = 496;
        const std::string WINDOW_TITTLE = "Pacman";
        std::vector<std::string> startMenuButtonText = {"New Game", "How to Play", "High Scores", "Sound: ON", "Exit"};

        Window();

        ~Window();

        void initSDL();

        void quitSDL();

        void runGame();

};

#endif // _WINDOW_H_
