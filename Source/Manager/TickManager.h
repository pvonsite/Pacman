#pragma once

#ifndef _TICKMANAGER_H_
#define _TICKMANAGER_H_

#include <SDL.h>
#include <stack>

typedef std::pair<const int, int> CII;

class TickManager {
    private:
        Uint32 lastTick;

        std::stack<CII> mode;

        int lastStatus;
        bool pause;
        int FRIGHTEN_TIME = 5;
        int SCATTERING_TIME = 7;
        int CHASING_TIME = 20;
    public:
        const int FRIGHTEN_MODE = 0;
        const int SCATTERING_MODE = 1;
        const int CHASING_MODE = 2;
        const int oo = -1;

        TickManager();

        bool isScatteringTime() const;

        void setFrightenTime();

        void resetTick(const int level);

        void updateStatus();

        bool pauseTick(const bool status);
};

#endif // TIMEMANAGER_H_
