#include "TextureSrc.h"

bool TextureSrc::pacmanIsDead() {
    if (pacmanFrame == 110) {
        pacmanFrame = 0; return true;
    }
    return false;
}

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
        posTexX = 0;
        for (int i = 0; i < 11; ++i) pacmanDEAD[i] = {posTexX, 155, 30, 30}, posTexX += 31;

        Console->Status("Pacman Texture got successfully!");

        /// Ghost setup
        posTexX = 0; posTexY = 31;
        for (int i = 0; i < TOTAL_GHOST - 1; ++i) {
            ghost[i][UP   ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][UP   ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][FRIGHTEN_GHOST][0] = {posTexX, 31, 30, 30}; posTexX += 31;
            ghost[i][FRIGHTEN_GHOST][1] = {posTexX, 31, 30, 30}; posTexX = 0;
            posTexY += 31;
        }
        posTexX = 248; posTexY = 62;
        ghost[GHOST_SPIRIT][UP   ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_SPIRIT][UP   ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
        ghost[GHOST_SPIRIT][DOWN ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_SPIRIT][DOWN ][1] = {posTexX, posTexY, 30, 30}; posTexX = 248; posTexY += 31;
        ghost[GHOST_SPIRIT][LEFT ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_SPIRIT][LEFT ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
        ghost[GHOST_SPIRIT][RIGHT][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_SPIRIT][RIGHT][1] = {posTexX, posTexY, 30, 30}; posTexX = posTexY = 0;

        Console->Status("Ghost Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7, posY - 7, 30, 30};
    ++pacmanFrame;

    if (status != DEAD_PACMAN && pacmanFrame == 30) pacmanFrame = 0;

    switch (status) {
        case -1: srcRect = pacmanUP[0]; break;
        case UP:    srcRect = pacmanUP   [ pacmanFrame / 10 ]; break;
        case RIGHT: srcRect = pacmanRIGHT[ pacmanFrame / 10 ]; break;
        case DOWN:  srcRect = pacmanDOWN [ pacmanFrame / 10 ]; break;
        case LEFT:  srcRect = pacmanLEFT [ pacmanFrame / 10 ]; break;
        case DEAD_PACMAN: srcRect = pacmanDEAD[pacmanFrame / 10]; break;
    }

    SDL_RenderCopy(renderer, pacmanTexture, &srcRect, &dsRect);
}

void TextureSrc::renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY, int ghostID, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7, posY - 7, 30, 30};
    ++ghostFrame[ghostID];

    if (ghostFrame[ghostID] == 14) ghostFrame[ghostID] = 0;

    switch (status) {
        case UP:    srcRect = ghost[ ghostID ][UP   ][ ghostFrame[ghostID] / 7 ]; break;
        case RIGHT: srcRect = ghost[ ghostID ][RIGHT][ ghostFrame[ghostID] / 7 ]; break;
        case DOWN:  srcRect = ghost[ ghostID ][DOWN ][ ghostFrame[ghostID] / 7 ]; break;
        case LEFT:  srcRect = ghost[ ghostID ][LEFT ][ ghostFrame[ghostID] / 7 ]; break;
        case FRIGHTEN_GHOST: srcRect = ghost[ghostID][FRIGHTEN_GHOST][ghostFrame[ghostID] / 7]; break;
    }

    SDL_RenderCopy(renderer, ghostTexture, &srcRect, &dsRect);
}
