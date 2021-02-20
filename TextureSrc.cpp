#include "TextureSrc.h"

void TextureSrc::loadTileTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("Pacman Tile Labyrinth.png");

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        tileTexture = SDL_CreateTextureFromSurface(renderer, Image);

        int cnt = -1;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 4; ++j) {
                tileSprite[++cnt] = {i * 8, j * 8, 8, 8};
            }
        }
        std::cout << cnt;

        //tileSprite[26].h = 7;

        Console->Status("Tile Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect) {
    SDL_RenderCopy(renderer, tileTexture, &tileSprite[ tileID ], dsRect);
}
