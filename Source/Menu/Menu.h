#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "../Manager/LogStatus.h"
#include "Button.h"

class Menu {
    private:
        int alphaMod = 1;
        int arrowHSPos;
        int currentButtonID;
        int currentMenuStatus;
        int currentHTPid;

        int TOTAL_BUTTON;
        int MENU_BUTTON_WIDTH;
        int MENU_BUTTON_HEIGHT;
        int baseScrPosX;
        int baseScrPosY;

        TextManager* scoreText = nullptr;
        Mix_Chunk* navigationSound = Mix_LoadWAV("Source/Assets/Sound/button.wav");
        Mix_Chunk* selectionSound = Mix_LoadWAV("Source/Assets/Sound/button.wav");
        SDL_Texture* menuTexture;
        SDL_Texture* howToPlayTexture[3];
        SDL_Texture* highScoreTexture;
        SDL_Texture* arrowTexture;
        std::vector<Button* > menuButton;

        LogStatus* console = new LogStatus("Menu");
        bool running = false;

        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath);
    public:
        static const int RESUME = 0;
        static const int RUNNING = 1;
        static const int PLAY_BUTTON_PRESSED = 2;
        static const int EXIT_BUTTON_PRESSED = 3;
        static const int HOW_TO_PLAY = 4;
        static const int HIGH_SCORES = 5;
        static const bool ON = true;
        static const bool OFF = false;

        Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight);

        ~Menu();

        void init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string> &buttonText);

        void render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData);

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer);

        bool isRunning() const;

        int getStatus() const;

        void reOpen();

        void changeRunStatus();

        bool getSoundState() const;
};

#endif // _MENU_H_
