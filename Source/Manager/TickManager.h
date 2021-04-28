#pragma once

#ifndef _TICKMANAGER_H_
#define _TICKMANAGER_H_

#include <SDL.h>
#include <stack>

typedef std::pair<const int, double> CID;

class TickManager {
    private:
        Uint32 lastTick;
        Uint32 FlastTick;
        Uint32 GlastTick;
        Uint32 lastFrame = 0;

        std::stack<CID> mode;

        int lastStatus;
        bool pause;
        double FRIGHTEN_TIME = 5.0;
        double SCATTERING_TIME = 7.0;
        double CHASING_TIME = 20.0;
    public:
        const int FPS = 60;
        const double FRIENDY_CHASE_TIME = 3.0;
        const double GREENDY_CHASE_TIME = 2.0;
        const int FRIGHTEN_MODE = 0;
        const int SCATTERING_MODE = 1;
        const int CHASING_MODE = 2;
        const double oo = -1;

        TickManager();

        double remainFrightenTime() const;

        bool isFrightenTime() const;

        bool isScatteringTime() const;

        bool isFriendyChaseTime() const;

        bool isGreendyChaseTime() const;

        void friendyStartChasePacman();

        void greendyStartChasePacman();

        void setFrightenTime();

        void resetTick(const int level);

        void updateStatus();

        void stablizeFPS();

        bool pauseTick(const bool status);
};

#endif // TIMEMANAGER_H_
