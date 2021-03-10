#include "TickManager.h"
#include <iostream>

TickManager::TickManager() {
    lastTick = SDL_GetTicks();
    mode.push( CII(CHASING_MODE, oo) );
    mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CII(CHASING_MODE, CHASING_TIME) );
    mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CII(CHASING_MODE, CHASING_TIME) );
    mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CII(CHASING_MODE, CHASING_TIME) );
    mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
}

bool TickManager::isScatteringTime() const {
    return mode.top().first == SCATTERING_MODE;
}

void TickManager::setFrightenTime() {
    lastStatus = mode.top().first;
    mode.pop();
    if (lastStatus == CHASING_MODE)
        mode.push( CII(CHASING_MODE, CHASING_TIME - (SDL_GetTicks() - lastTick)) );
    else if (lastStatus == SCATTERING_MODE)
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME - (SDL_GetTicks() - lastTick)) );
    mode.push( CII(FRIGHTEN_MODE, FRIGHTEN_TIME) );
    lastTick = SDL_GetTicks();
}

void TickManager::resetTick(const int level) {
    while (!mode.empty()) mode.pop();
    if (level == 1) {
        mode.push( CII(CHASING_MODE, oo) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 5;
    }
    else if (level < 5) {
        mode.push( CII(CHASING_MODE, oo) );
        mode.push( CII(SCATTERING_MODE, 1) );
        mode.push( CII(CHASING_MODE, 1033) );
        mode.push( CII(SCATTERING_MODE, 5) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 3;
    }
    else {
        mode.push( CII(CHASING_MODE, oo) );
        mode.push( CII(SCATTERING_MODE, 1) );
        mode.push( CII(CHASING_MODE, 1037) );
        mode.push( CII(SCATTERING_MODE, 5) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CII(CHASING_MODE, CHASING_TIME) );
        mode.push( CII(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 1;
    }
    lastTick = SDL_GetTicks();
}

void TickManager::updateStatus() {
    if (pause == true) {
        lastTick = SDL_GetTicks();
        return;
    }
    int timePass = (SDL_GetTicks() - lastTick) / 1000;

    if (!mode.empty()) {
        if (timePass > mode.top().second && mode.top().second != oo) {
            mode.pop(); lastTick = SDL_GetTicks();
        }
    }
}

bool TickManager::pauseTick(const bool status) {
    return pause = status;
}
