#include "TickManager.h"
#include <iostream>

TickManager::TickManager() {
    lastTick = SDL_GetTicks();
    mode.push( CID(CHASING_MODE, oo) );
    mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CID(CHASING_MODE, CHASING_TIME) );
    mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CID(CHASING_MODE, CHASING_TIME) );
    mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    mode.push( CID(CHASING_MODE, CHASING_TIME) );
    mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
}

bool TickManager::isScatteringTime() const {
    return mode.top().first == SCATTERING_MODE;
}

void TickManager::setFrightenTime() {
    lastStatus = mode.top().first;
    mode.pop();
    if (lastStatus == CHASING_MODE)
        mode.push( CID(CHASING_MODE, CHASING_TIME - (SDL_GetTicks() - lastTick)) );
    else if (lastStatus == SCATTERING_MODE)
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME - (SDL_GetTicks() - lastTick)) );
    mode.push( CID(FRIGHTEN_MODE, FRIGHTEN_TIME) );
    lastTick = SDL_GetTicks();
}

bool TickManager::isFriendyChaseTime() const {
    double timePass = (SDL_GetTicks() - FlastTick) / 1000.0;
    return (timePass <= FRIENDY_CHASE_TIME);
}

bool TickManager::isGreendyChaseTime() const {
    double timePass = (SDL_GetTicks() - GlastTick) / 1000.0;
    return (timePass <= GREENDY_CHASE_TIME);
}

void TickManager::friendyStartChasePacman() {
    FlastTick = SDL_GetTicks();
}

void TickManager::greendyStartChasePacman() {
    GlastTick = SDL_GetTicks();
}

void TickManager::resetTick(const int level) {
    while (!mode.empty()) mode.pop();
    if (level == 1) {
        mode.push( CID(CHASING_MODE, oo) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 5.0;
    }
    else if (level < 5) {
        mode.push( CID(CHASING_MODE, oo) );
        mode.push( CID(SCATTERING_MODE, 1.0) );
        mode.push( CID(CHASING_MODE, 1033.0) );
        mode.push( CID(SCATTERING_MODE, 5.0) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 3.0;
    }
    else {
        mode.push( CID(CHASING_MODE, oo) );
        mode.push( CID(SCATTERING_MODE, 1.0) );
        mode.push( CID(CHASING_MODE, 1037.0) );
        mode.push( CID(SCATTERING_MODE, 5.0) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        mode.push( CID(CHASING_MODE, CHASING_TIME) );
        mode.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 1.0;
    }
    lastTick = SDL_GetTicks();
}

void TickManager::updateStatus() {
    if (pause == true) {
        lastTick = SDL_GetTicks();
        return;
    }
    double timePass = (SDL_GetTicks() - lastTick) / 1000.0;

    if (!mode.empty()) {
        if (timePass > mode.top().second && mode.top().second != oo) {
            mode.pop(); lastTick = SDL_GetTicks();
        }
    }
}

bool TickManager::pauseTick(const bool status) {
    return pause = status;
}

bool TickManager::isFrightenTime() const {
    return mode.top().first == FRIGHTEN_MODE;
}

double TickManager::remainFrightenTime() const {
    return FRIGHTEN_TIME - (SDL_GetTicks() - lastTick) / 1000.0;
}
