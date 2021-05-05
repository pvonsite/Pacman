#include "PlayStateManager.h"

#include <iostream>

using namespace std;

PlayStateManager::PlayStateManager() {
    engine = new Engine();
    pauseMenu = new Menu(262, 170, pauseMenuButtonText.size(), 320, 30);
    runPauseMenu = false;
}

PlayStateManager::~PlayStateManager() {
    delete engine;
    engine = nullptr;

    runPauseMenu = false;
}

void PlayStateManager::newGame(SDL_Renderer* &renderer) {
    static bool inited = false;
    if (!inited) {
        this->scoreData = scoreData;
        pauseMenu->init(renderer, "Source/Assets/Menu Image/Pacman Pause Menu.png", pauseMenuButtonText);
        engine->init(renderer);
        inited = true;
    }
    else {
        engine->newGame();
    }
}

void PlayStateManager::runGame(bool &exitToMenu) {
    if (runPauseMenu == false) engine->loop(exitToMenu);
}

void PlayStateManager::handleEvent(SDL_Event& e, SDL_Renderer* &renderer, bool &exitToMainMenu, std::vector<std::string> &scoreData) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        runPauseMenu = true;
        pauseMenu->reOpen();
        while (!muteChannel.empty()) muteChannel.pop_back();
        for (int channel = 1; channel <= 8; ++channel) {
            if (Mix_Paused(channel) == 0) {
                Mix_Pause(channel);
                muteChannel.push_back(channel);
            }
        }
    }
    else {
        if (runPauseMenu) {
            pauseMenu->handleEvent(e, renderer);
            switch (pauseMenu->getStatus()) {
                case Menu::RESUME:
                    runPauseMenu = false;
                    for (int channel : muteChannel) Mix_Resume(channel);
                    break;
                case Menu::PLAY_BUTTON_PRESSED:
                    runPauseMenu = false;
                    engine->newGame();
                    break;
                case Menu::EXIT_BUTTON_PRESSED:
                    exitToMainMenu = true;
                    runPauseMenu = false; break;
            }
        }
        else engine->handleEvent(e, scoreData);
    }
}

void PlayStateManager::render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData) {
    if (runPauseMenu) pauseMenu->render(renderer, scoreData);
    else engine->render(renderer, scoreData);
}
