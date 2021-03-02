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

        SDL_Texture* pacmanTexture;
        SDL_Rect pacmanUP[3];
        SDL_Rect pacmanDOWN[3];
        SDL_Rect pacmanLEFT[3];
        SDL_Rect pacmanRIGHT[3];
        SDL_Rect pacmanDEAD[11];

        SDL_Texture* ghostTexture;
        SDL_Rect ghost[5][5][2];
    public:
        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;

        static const int FRIGHTEN_GHOST = 4;
        static const int DEAD_PACMAN = 5;

        static const int BLINKY = 0;
        static const int PINKY  = 1;
        static const int INKY   = 2;
        static const int CLYDE  = 3;
        static const int GHOST_SPIRIT = 4;
        static const int TOTAL_GHOST = 5;

        TextureSrc() {
            tileTexture = nullptr;
            pacmanTexture = nullptr;
            ghostTexture = nullptr;
        }

        ~TextureSrc() {
            SDL_DestroyTexture(tileTexture);
            tileTexture = nullptr;

            SDL_DestroyTexture(pacmanTexture);
            pacmanTexture = nullptr;

            SDL_DestroyTexture(ghostTexture);
            ghostTexture = nullptr;
        }

        void loadTileTexture(SDL_Renderer* &renderer);

        void renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect);

        void loadPacmanAndGhostTexture(SDL_Renderer* &renderer);

        void renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int dir, int &frame);

        void renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY, int ghostID, int dir, int &frame);
};

#endif // _TEXTURESRC_H_
