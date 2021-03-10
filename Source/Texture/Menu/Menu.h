#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <SDL.h>
#include <SDL_image.h>
#include "../../Manager/LogStatus.h"

class Menu {
    private:
        SDL_Texture* menuTexture;

        LogStatus* console = new LogStatus("Menu");
    public:
        Menu();

        ~Menu();

        void init(SDL_Renderer* &renderer);

        void render(SDL_Renderer* &renderer);
};

#endif // _MENU_H_
