#pragma once

#ifndef _PLAYSTATEMANAGER_H_
#define _PLAYSTATEMANAGER_H_

#include <string>
#include <vector>
#include "Engine.h"
#include "SDL_mixer.h"
#include "../Menu/Button.h"
#include "../Menu/Menu.h"

class PlayStateManager {
    private:
        std::vector<std::string> scoreData;
        std::vector<int> muteChannel;
        Engine* engine = nullptr;
        Menu* pauseMenu = nullptr;
        bool running = true;
        bool runPauseMenu = false;
    public:
        std::vector<std::string> pauseMenuButtonText = {"Resume", "New Game", "How to Play", "Sound: ON", "Exit to Start Menu"};
        PlayStateManager();

        ~PlayStateManager();

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer, bool &runningMain, std::vector<std::string> &scoreData);

        void newGame(SDL_Renderer* &renderer);

        void runGame(bool &exitToMenu);

        void render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData);
};

#endif // _PLAYSTATEMANAGER_H_
