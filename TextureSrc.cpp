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

        Console->Status("Tile Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect) {
    SDL_RenderCopy(renderer, tileTexture, &tileSprite[ tileID ], dsRect);
}

void TextureSrc::loadPacmanTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("things.png");

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        pacmanTexture = SDL_CreateTextureFromSurface(renderer, Image);

        /// Pacman goes up
        for (int i = 0; i < 3; ++i) pacmanUP[i] = {0, i * 15, 15, 15};
        /// Pacman goes down
        for (int i = 3; i < 6; ++i) pacmanDOWN[i % 3] = {0, i * 15, 15, 15};
        /// Pacman goes left
        for (int i = 6; i < 9; ++i) pacmanLEFT[i % 3] = {0, i * 15, 15, 15};
        /// Pacman goes right
        for (int i = 9; i < 12; ++i) pacmanRIGHT[i % 3] = {0, i * 15, 15, 15};
        /// Pacman dead
        for (int i = 0; i < 11; ++i) pacmanDEAD[i] = {75, i * 15, 15, 15};

        Console->Status("Pacman Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int dir) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7, posY - 7, 30, 30};
    switch (dir) {
        case 1: srcRect = pacmanUP[0]; break;
        case 2: srcRect = pacmanRIGHT[0]; break;
        case 3: srcRect = pacmanDOWN[0]; break;
        case 4: srcRect = pacmanLEFT[0]; break;
        case 5: srcRect = pacmanDEAD[0]; break;
    }

    SDL_RenderCopy(renderer, pacmanTexture, &srcRect, &dsRect);
}

