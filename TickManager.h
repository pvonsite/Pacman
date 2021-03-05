#pragma once

#ifndef _TICKMANAGER_H_
#define _TICKMANAGER_H_

#include <SDL.h>

class TickManager {
    private:
        Uint32 lastTick;

        int currentStatus;
    public:
        static const int FRIGHTEN_MODE = 0;
        static const int SCATTERING_MODE = 1;
        static const int CHASING_MODE = 2;

        TickManager();

        int getStatus() const;

        void setStatus(const int status);

        Uint32 getTime();

        void resetTick();

        void updateStatus();

};

#endif // TIMEMANAGER_H_
