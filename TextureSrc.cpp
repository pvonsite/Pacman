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

void TextureSrc::loadPacmanAndGhostTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("Pacman and Ghost Texture.png");
    //SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 0, 0, 0));
    //SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 1, 1, 1));

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        pacmanTexture = SDL_CreateTextureFromSurface(renderer, Image);
        ghostTexture = pacmanTexture;

        int posTexX = 0, posTexY = 0;

        /// Pacman goes up
        for (int i = 0; i < 3; ++i)  pacmanUP[i] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes down
        for (int i = 3; i < 6; ++i)  pacmanDOWN[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes left
        for (int i = 6; i < 9; ++i)  pacmanLEFT[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes right
        for (int i = 9; i < 12; ++i) pacmanRIGHT[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman dead
        for (int i = 0; i < 11; ++i) pacmanDEAD[i] = {posTexX, 155, 30, 30}, posTexX += 31;

        Console->Status("Pacman Texture got successfully!");

        /// Ghost setup
        posTexX = 0; posTexY = 31;
        for (int i = 0; i < TOTAL_GHOST; ++i) {
            ghost[i][UP   ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][UP   ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][1] = {posTexX, posTexY, 30, 30}; posTexX = 0;
            posTexY += 31;
        }
        posTexX = 0; posTexY = 31;
        frightenedGhost[0] = {248, posTexY, 30, 30};
        frightenedGhost[1] = {279, posTexY, 30, 30};

        Console->Status("Ghost Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int dir, int &frame) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7, posY - 7, 30, 30};

    if (frame == 30) frame = 0;
    int pacmanFrame = frame / 10;

    switch (dir) {
        case 0: srcRect = pacmanUP[0]; break;
        case UP:    srcRect = pacmanUP   [ pacmanFrame ]; break;
        case RIGHT: srcRect = pacmanRIGHT[ pacmanFrame ]; break;
        case DOWN:  srcRect = pacmanDOWN [ pacmanFrame ]; break;
        case LEFT:  srcRect = pacmanLEFT [ pacmanFrame ]; break;
        case 5: srcRect = pacmanDEAD[0]; break;
    }

    SDL_RenderCopy(renderer, pacmanTexture, &srcRect, &dsRect);
}

void TextureSrc::renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY, int ghostID, int dir, int &frame) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7, posY - 7, 30, 30};

    if (frame == 14) frame = 0;
    int ghostFrame = frame / 7;

    switch (dir) {
        case 0: srcRect = ghost[ghostID][UP][ghostFrame]; break;
        case UP:    srcRect = ghost[ ghostID ][UP   ][ ghostFrame ]; break;
        case RIGHT: srcRect = ghost[ ghostID ][RIGHT][ ghostFrame ]; break;
        case DOWN:  srcRect = ghost[ ghostID ][DOWN ][ ghostFrame ]; break;
        case LEFT:  srcRect = ghost[ ghostID ][LEFT ][ ghostFrame ]; break;
        //case 5: srcRect = pacmanDEAD[0]; break;
    }

    SDL_RenderCopy(renderer, ghostTexture, &srcRect, &dsRect);
}
