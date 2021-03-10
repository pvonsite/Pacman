#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

class GameManager {
    private:
        int level;
        int eatenCoins;
        int points;
    public:
        const int TOTAL_COINS = 244;

        GameManager();

        void eatCoins();

        int getEatenCoins() const;

        void nextLevel();

        bool clearAllCoins() const;

        int getLevel() const;
};

#endif // GAMEMANAGER_H_
