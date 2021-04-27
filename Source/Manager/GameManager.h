#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "../Object/Ghost.h"
#include "TextManager.h"
#include "../Menu/Button.h"

class GameManager {
    private:
        int level;
        int life;
        int eatenCoins;
        int eatenGhost;
        int scores;
        int pos = -1;
        std::string playername = "";
        int playerDecision;
        int currentBut;
        bool newRecord = false;
        int ghostEatenPosX;
        int ghostEatenPosY;

        int PINKY_COIN_LIMIT;
        int INKY_COIN_LIMIT;
        int CLYDE_COIN_LIMIT;

        TextManager* levelText;
        TextManager* liveText;
        TextManager* scoreText;
        TextManager* playerName;

        SDL_Texture* egBoard;
        SDL_Texture* hsBoard;
        Button* yesBut;
        Button* noBut;
        Mix_Chunk* navigationSound = Mix_LoadWAV("Source/Assets/Sound/button.wav");
    protected:
        SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imagePath);
    public:
        const int TOTAL_COINS = 244;
        static const int normalCoin = 26;
        static const int superCoin = 27;
        static const int notCoin = 0;
        static const int pauseGame = 1;
        static const int AGAIN = 2;
        static const int QUIT  = 3;
        static const int WAITING = 4;

        GameManager(SDL_Renderer* &renderer);

        ~GameManager();

        void reset();

        void nextLevel();

        void eatCoins(const int typeOfCoin);

        void eatGhost(const int ghostTileX, const int ghostTileY);

        void lostALife();

        int getEatenGhostStreak() const;

        int getEatenGhostPosX() const;

        int getEatenGhostPosY() const;

        int getRemainLife() const;

        bool clearAllCoins() const;

        int getLevel() const;

        int getPlayerDecision() const;

        int getRemainCoin() const;

        void handleGhostPos(Ghost* &pinky, Ghost* &inky, Ghost* &clyde, Ghost* &greendy);

        void handleEGBoard(SDL_Event &e, std::vector<std::string> &scoreData);

        void renderHUD(SDL_Renderer* &renderer);

        void runEGBoard(SDL_Renderer* &renderer);

        void checkScoreData(const std::vector<std::string> &scoreData);
};

#endif // GAMEMANAGER_H_
