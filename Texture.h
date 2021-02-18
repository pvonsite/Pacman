#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include "Log.h"

class Texture {
    private:
        SDL_Rect blockSprite[32];
        SDL_Texture* blockTexture;

    public:
        Texture() {
            blockTexture = nullptr;
            for (int i = 0; i < 32; ++i) blockSprite[i] = {0, 0, 0, 0};
        }

        ~Texture() {
            SDL_DestroyTexture(blockTexture);
            blockTexture = nullptr;

        }

        void loadTexture(SDL_Renderer* &renderer);

};

#endif // _TEXTURE_H_

