#include "GameManager.h"

 GameManager::GameManager() {
    level = 1;
    eatenCoins = 0;
}

void GameManager::eatCoins() {
    ++eatenCoins;
}

int GameManager::getEatenCoins() const {
    return eatenCoins;
}

void GameManager::nextLevel() {
    ++level;
    eatenCoins = 0;
}

bool GameManager::clearAllCoins() const {
    return eatenCoins == TOTAL_COINS;
}

int GameManager::getLevel() const {
    return level;
}
