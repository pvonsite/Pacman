#include "Texture.h"

Log textureLog("Texture: ");



void Texture :: loadTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("labyrinth.png");

    if (Image == nullptr) {
        textureLog.Status( IMG_GetError() );
        return;
    }

    blockTexture = SDL_CreateTextureFromSurface(renderer, Image);

    int cnt = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            blockSprite[++cnt] = {8 * i, 8 * j, 8, 8};
        }
    }
    cnt = 0;

    Image = IMG_Load("things.png");

    if (Image == nullptr) {
        textureLog.Status( IMG_GetError() );
        return;
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}
