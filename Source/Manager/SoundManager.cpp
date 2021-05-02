#include "SoundManager.h"
#include <iostream>

using namespace std;

SoundManager::SoundManager() {
    for (int i = 0; i < 11; ++i)
        soundEffect[i] = nullptr;

    playList.clear();
    eatDotTime = 0;
    oldMoveType = -1;
    newMoveType = MOVE_0;
    ghostTurnBlue = false;
    ghostGoHome = false;
    dead = false;
}

SoundManager::~SoundManager() {
    for (int i = 0; i < 11; ++i) {
        Mix_FreeChunk(soundEffect[i]);
        soundEffect[i] = nullptr;
    }
}

void SoundManager::insertPlayList(const int soundID) {
    //cout << soundID << endl;
    if (soundID == EAT_DOT) eatDotTime = 16;
    else if (soundID == EAT_GHOST) Mix_PlayChannel(4, soundEffect[EAT_GHOST], 0);
    else if (soundID <= 3) newMoveType = soundID;
    else if (soundID == GHOST_GO_HOME) ghostGoHome = true;
    else if (soundID == REVIVAL_GHOST) ghostGoHome = false;
    else if (soundID == GHOST_TURN_BLUE) ghostTurnBlue = true;
    else if (soundID == NORMAL_GHOST) ghostTurnBlue = false;
    else if (soundID == DEAD) {
        dead = true;
        ghostGoHome = false;    Mix_Pause(6);
        ghostTurnBlue = false;  Mix_Pause(5);
        eatDotTime = 0;         Mix_Pause(3);
        Mix_Pause(1);
    }
    else if (soundID == START || soundID == WINNING) {
        dead = false;
        ghostGoHome = false;    Mix_Pause(6);
        ghostTurnBlue = false;  Mix_Pause(5);
        eatDotTime = 0;         Mix_Pause(3);
        Mix_Pause(1);
        if (soundID == WINNING) oldMoveType = MOVE_0;
        Mix_PlayChannel(2, soundEffect[soundID], 0);
    }
}

void SoundManager::loadSound() {
    soundEffect[ MOVE_0 ] = Mix_LoadWAV("Source/Assets/Sound/move 0.wav");
    soundEffect[ MOVE_1 ] = Mix_LoadWAV("Source/Assets/Sound/move 1.wav");
    soundEffect[ MOVE_2 ] = Mix_LoadWAV("Source/Assets/Sound/move 2.wav");
    soundEffect[ MOVE_3 ] = Mix_LoadWAV("Source/Assets/Sound/move 3.wav");
    soundEffect[ START  ] = Mix_LoadWAV("Source/Assets/Sound/start.wav");
    soundEffect[ DEAD   ] = Mix_LoadWAV("Source/Assets/Sound/dead.wav");
    soundEffect[ WINNING ] = Mix_LoadWAV("Source/Assets/Sound/next level.wav");
    soundEffect[ EAT_DOT ] = Mix_LoadWAV("Source/Assets/Sound/eat dot.wav");
    soundEffect[ EAT_GHOST ] = Mix_LoadWAV("Source/Assets/Sound/eat ghost.wav");
    soundEffect[ GHOST_GO_HOME ] = Mix_LoadWAV("Source/Assets/Sound/ghost go home.wav");
    soundEffect[ GHOST_TURN_BLUE ] = Mix_LoadWAV("Source/Assets/Sound/ghost turn blue.wav");

    for (int i = 0; i < 11; ++i) if (soundEffect == nullptr)
        Console->Status( Mix_GetError() );

    /*
        8 channels
        move 0->3 : channel 1
        dead start: channel 2
        eat dot: channel 3
        eat ghost: channel 4
        ghost turn blue: channel 5
        ghost go home: channel 6
    */
    Mix_PlayChannel(1, soundEffect[MOVE_0], -1);            Mix_Pause(1);
    Mix_PlayChannel(3, soundEffect[EAT_DOT], -1);           Mix_Pause(3);
    Mix_PlayChannel(5, soundEffect[GHOST_TURN_BLUE], -1);   Mix_Pause(5);
    Mix_PlayChannel(6, soundEffect[GHOST_GO_HOME], -1);     Mix_Pause(6);
    Mix_Pause(8);
}

void SoundManager::playSound() {
    /// channel 1
    if (dead) {
        Mix_PlayChannel(2, soundEffect[DEAD], 0);
        dead = false;
    }
    if (Mix_Playing(2)) return;
    if (newMoveType != oldMoveType) {
        Mix_PlayChannel(1, soundEffect[newMoveType], -1);
        oldMoveType = newMoveType;
    }
    if (eatDotTime > 0) {
        --eatDotTime;
        Mix_Resume(3);
    }
    else Mix_Pause(3);
    if (ghostTurnBlue) Mix_Resume(5);
    else Mix_Pause(5);
    if (ghostGoHome) {
        Mix_Resume(6);
        if (ghostTurnBlue) Mix_Pause(5);
    }
    else {
        Mix_Pause(6);
        if (ghostTurnBlue) Mix_Resume(5);
    }
}

void SoundManager::reset() {
    Mix_PlayChannel(1, soundEffect[oldMoveType], -1);
}
