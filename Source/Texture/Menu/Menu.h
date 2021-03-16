#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <SDL.h>
#include <SDL_image.h>
#include "../../Manager/LogStatus.h"
#include "../Button.h"

class Menu {
    private:
        int currentButtonID;
        int currentMenuStatus;

        SDL_Texture* menuTexture;
        Button* menuButton[3];

        LogStatus* console = new LogStatus("Menu");
    public:
        static const int MENU_BUTTON_WIDTH = 150;
        static const int MENU_BUTTON_HEIGHT = 30;
        static const int RUNNING = 0;
        static const int PLAY_BUTTON_PRESSED = 1;
        static const int EXIT_BUTTON_PRESSED = 2;

        Menu();

        ~Menu();

        void init(SDL_Renderer* &renderer);

        void render(SDL_Renderer* &renderer);

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer);

        int getStatus() const;
};

#endif // _MENU_H_
