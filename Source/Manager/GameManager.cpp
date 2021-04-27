#include "GameManager.h"
#include <iostream>
#include <string>

GameManager::GameManager(SDL_Renderer* &renderer) {
    level = 1;
    life = 3;
    eatenCoins = 0;
    scores = 0;
    playername = "Unknown";
    playerDecision = WAITING;
    currentBut = 1;
    PINKY_COIN_LIMIT = 5;
    INKY_COIN_LIMIT = 30;
    CLYDE_COIN_LIMIT = 90;
    liveText = new TextManager(28);
    liveText->loadRenderText(renderer, "Lives:", {255, 255, 255, 255});
    scoreText = new TextManager(28);
    scoreText->loadRenderText(renderer, "Scores: 0", {255, 255, 255, 255});
    levelText = new TextManager(28);
    levelText->loadRenderText(renderer, "Level: 1", {255, 255, 255, 255});
    playerName = new TextManager(20);
    playerName->loadRenderText(renderer, playername.c_str(), {255, 255, 255, 255});
    egBoard = loadImage(renderer, "Source/Assets/Menu Image/endgame.png");
    hsBoard = loadImage(renderer, "Source/Assets/Menu Image/newHighscore.png");
    yesBut = new Button(70, 30, 478, 250); yesBut->loadButton(renderer, "Yes"); yesBut->setStatus(Button::BUTTON_IN);
    noBut  = new Button(70, 30, 580, 250); noBut ->loadButton(renderer, "No");  noBut ->setStatus(Button::BUTTON_OUT);
}

GameManager::~GameManager() {
    delete levelText;
    levelText = nullptr;
    delete liveText;
    liveText = nullptr;
    delete scoreText;
    scoreText = nullptr;
    delete egBoard;
    egBoard = nullptr;
    delete hsBoard;
    hsBoard = nullptr;
    delete playerName;
    playerName = nullptr;
    Mix_FreeChunk(navigationSound);
}

SDL_Texture* GameManager::loadImage(SDL_Renderer* &renderer, const std::string imagePath) {
    SDL_Surface* Image = IMG_Load(imagePath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void GameManager::reset() {
    level = 1;
    life = 3;
    scores = 0;
    eatenCoins = 0;
    currentBut = 1;
    PINKY_COIN_LIMIT = 5;
    INKY_COIN_LIMIT = 30;
    CLYDE_COIN_LIMIT = 90;
    playerDecision = WAITING;
    pos = -1;
}

void GameManager::eatCoins(const int typeOfCoin) {
    ++eatenCoins;
    if (typeOfCoin == normalCoin) scores += 10;
    else if (typeOfCoin == superCoin) {
        eatenGhost = -1;
        scores += 50;
    }
}

void GameManager::eatGhost(const int ghostTileX, const int ghostTileY) {
    (++eatenGhost) %= 4;
    switch (eatenGhost) {
        case 0: scores += 200; break;
        case 1: scores += 400; break;
        case 2: scores += 800; break;
        case 3: scores += 1600; break;
    }
    ghostEatenPosX = ghostTileX;
    ghostEatenPosY = ghostTileY;
}

void GameManager::lostALife() {
    --life;
}

int GameManager::getEatenGhostStreak() const {
    return eatenGhost;
}

int GameManager::getEatenGhostPosX() const {
    return ghostEatenPosX;
}

int GameManager::getEatenGhostPosY() const {
    return ghostEatenPosY;
}

int GameManager::getRemainLife() const {
    return life;
}

void GameManager::nextLevel() {
    ++level;
    eatenCoins = 0;
    if (level <= 3) {
        PINKY_COIN_LIMIT = 5;
        INKY_COIN_LIMIT = 30;
        CLYDE_COIN_LIMIT = 90;
    }
    else if (level <= 5) {
        PINKY_COIN_LIMIT = 0;
        INKY_COIN_LIMIT  = 5;
        CLYDE_COIN_LIMIT = 10;
    }
    else PINKY_COIN_LIMIT = INKY_COIN_LIMIT = CLYDE_COIN_LIMIT = 0;
}

bool GameManager::clearAllCoins() const {
    return eatenCoins == TOTAL_COINS;
}

int GameManager::getLevel() const {
    return level;
}

void GameManager::handleGhostPos(Ghost* &pinky, Ghost* &inky, Ghost* &clyde, Ghost* &greendy) {
    if (pinky->isInCage() && eatenCoins >= PINKY_COIN_LIMIT) pinky->respawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false);
    if (inky ->isInCage() && eatenCoins >=  INKY_COIN_LIMIT) inky ->respawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false);
    if (clyde->isInCage() && eatenCoins >= CLYDE_COIN_LIMIT) clyde->respawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false);
    if (getRemainCoin() < 100 && greendy != nullptr && greendy->isInCage()) greendy->respawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false);
}

void GameManager::renderHUD(SDL_Renderer* &renderer) {
    levelText->loadRenderText(renderer, "Level: " + std::to_string(level), {255, 255, 255, 255});
    levelText->renderText(renderer, 0, 0, TextManager::LEFT);
    liveText->loadRenderText(renderer, "Life: " + std::to_string(life), {255, 255, 255, 255});
    liveText->renderText(renderer, 0, 50, TextManager::LEFT);
    scoreText->loadRenderText(renderer, "Scores: " + std::to_string(scores), {255, 255, 255, 255});
    scoreText->renderText(renderer, 0, 100, TextManager::LEFT);
}

void GameManager::handleEGBoard(SDL_Event &e, std::vector<std::string> &scoreData) {
    if (newRecord) {
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_RETURN && playername.length() > 2) {
                Mix_PlayChannel(7, navigationSound, 0);
                SDL_StopTextInput();
                std::string data = playername + ": " + std::to_string(scores);
                scoreData.emplace(scoreData.begin() + pos, data.c_str());
                scoreData.pop_back();
                newRecord = false;
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE && playername.length() > 0) {
                playername.pop_back();
            }
            else if (e.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) ) {
                SDL_SetClipboardText(playername.c_str());
            }
            else if (e.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL)) {
                playername = SDL_GetClipboardText();
            }
        }
        else if (e.type == SDL_TEXTINPUT) {
            if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) && playername.length() < 22)
                if ((e.text.text[0] >= 'a' && e.text.text[0] <= 'z') || (e.text.text[0] >= 'A' && e.text.text[0] <= 'Z') || (e.text.text[0] >= '0' && e.text.text[0] <= '9') || e.text.text[0] == ' ')
                    playername += e.text.text;
        }
    }
    else {
        if (e.type == SDL_KEYDOWN) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
                currentBut = 2;
                noBut ->setStatus(Button::BUTTON_IN);
                yesBut->setStatus(Button::BUTTON_OUT);
            }
            else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
                currentBut = 1;
                yesBut->setStatus(Button::BUTTON_IN);
                noBut ->setStatus(Button::BUTTON_OUT);
            }
            else if (e.key.keysym.sym == SDLK_RETURN) {
                if (currentBut == 1) playerDecision = AGAIN;
                else playerDecision = QUIT;
            }
            return;
        }
    }
}

void GameManager::runEGBoard(SDL_Renderer* &renderer) {
    SDL_Rect dsRect = {441 - 250, 248 - 150, 500, 300};
    SDL_RenderCopy(renderer, egBoard, nullptr, &dsRect);
    yesBut->renderButton(renderer);
    noBut ->renderButton(renderer);
    if (newRecord) {
        SDL_RenderCopy(renderer, hsBoard, nullptr, &dsRect);
        static int caretTime = 0;
        SDL_Rect caret = {395 + playerName->getTextWidth(), 265, 2, 20};
        if (caretTime % 20 > 10) {
            SDL_RenderFillRect(renderer, &caret);
        }
        ++caretTime;
        caretTime %= 20;
        if (playername != "") {
            playerName->loadRenderText(renderer, playername.c_str(), {0, 0, 0, 255});
            playerName->renderText(renderer, 395, 268, TextManager::LEFT);
        }
    }
}

void GameManager::checkScoreData(const std::vector<std::string> &scoreData) {
    for (int i = 0; i < scoreData.size(); ++i) {
        int t = 0;
        int j = 0;
        while (j < scoreData[i].length() && scoreData[i][j] != ':') ++j;
        j += 2;
        while (j < scoreData[i].length()) t = t * 10 + scoreData[i][j] - '0', ++j;
        if (scores > t) {
            newRecord = true;
            SDL_StartTextInput();
            pos = i;
            break;
        }
    }
}

int GameManager::getPlayerDecision() const {
    return playerDecision;
}

int GameManager::getRemainCoin() const {
    return TOTAL_COINS - eatenCoins;
}

