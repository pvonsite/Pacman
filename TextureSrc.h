#pragma once

#ifndef _TEXTURESRC_H_
#define _TEXTURESRC_H_

#include <SDL.h>
#include <SDL_image.h>
#include "LogStatus.h"

class TextureSrc {
    private:
        LogStatus* Console = new LogStatus("TextureSrc");

        SDL_Texture* tileTexture;
        SDL_Rect tileSprite[32];
    public:
        TextureSrc() {
            tileTexture = nullptr;
        }

        ~TextureSrc() {
            SDL_DestroyTexture(tileTexture);
            tileTexture = nullptr;
        }

        void loadTileTexture(SDL_Renderer* &renderer);

        void renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect);
};

#endif // _TEXTURESRC_H_
