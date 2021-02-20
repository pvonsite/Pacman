#include "TextureSrc.h"

void TextureSrc::loadTileTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("Pacman Tile Labyrinth.png");

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        tileTexture = SDL_CreateTextureFromSurface(renderer, Image);

        int x = 0, y = 0;
        for (int i = 0; i < 32; ++i) {
            tileSprite[i] = {x, y, 16, 16};
            y += 17;
            if (i % 4 == 3) x += 17, y = 0;
        }

        //tileSprite[26].h = 7;

        Console->Status("Tile Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect) {
    SDL_RenderCopy(renderer, tileTexture, &tileSprite[ tileID ], dsRect);
}
