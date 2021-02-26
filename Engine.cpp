#include "Engine.h"
#include <limits>

using namespace std;

typedef std::pair<int, int> II;
typedef std::pair<int, std::pair<int, int> > IP;

void Engine::init(SDL_Renderer* &renderer) {
    map = new Map();
    map->findingCrossRoad();
    map->NextCrossTileID();
    pacman = new Pacman();
    blinky = new Ghost(13, 11); /// 13 11
    pinky  = new Ghost(13, 11); /// 13 14
    inky   = new Ghost(11, 11); /// 11 14
    clyde  = new Ghost(15, 11); /// 15 14
    objectTexture = new TextureSrc();
    objectTexture->loadTileTexture(renderer);
    objectTexture->loadPacmanAndGhostTexture(renderer);
    //pacman->pushtoStack(1);
}

void Engine::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT
         || e.key.keysym.sym == SDLK_s    || e.key.keysym.sym == SDLK_w  || e.key.keysym.sym == SDLK_a    || e.key.keysym.sym == SDLK_d    ) {
            int newDir  = 0;
            int lastDir = 0;
            int pacmanTileX = pacman->getTileX();
            int pacmanTileY = pacman->getTileY();
            int pacmanPosX  = pacman->getPosX();
            int pacmanPosY  = pacman->getPosY();

            if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

            switch (e.key.keysym.sym) {
                case SDLK_UP   : newDir = 1; break;
                case SDLK_DOWN : newDir = 3; break;
                case SDLK_LEFT : newDir = 4; break;
                case SDLK_RIGHT: newDir = 2; break;
                case SDLK_w    : newDir = 1; break;
                case SDLK_s    : newDir = 3; break;
                case SDLK_a    : newDir = 4; break;
                case SDLK_d    : newDir = 2; break;
            }

            cout << lastDir << " " << newDir << endl;
            if (lastDir == 0) {
                if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                    //pacman->eraseSpecial();
                    cout << 3;
                    pacman->pushtoStack(newDir);
                }
            }
            else {
                if (newDir % 2 == lastDir % 2) {
                    if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                        pacman->pushtoStack(newDir);
                        if (!pacman->emptySpecial()) pacman->eraseSpecial();
                    }
                }
                else {
                    std::pair<int, int> nextCross = map->getnextCrossID(pacmanTileX, pacmanTileY, lastDir);

                    if (lastDir % 2 == 0 && newDir % 2 == 1) {
                        if (pacmanPosY == pacmanTileY * 16) {
                            if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                                    pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
                            }
                            else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 32) {
                                pacman->pushSpecialStack( newDir, nextCross );
                            }
                        }
                    }
                    else if (lastDir % 2 == 1 && newDir % 2 == 0) {
                        if (pacmanPosX == pacmanTileX * 16) {
                            if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                                    pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
                            }
                            else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosY - nextCross.second * 16) <= 32) {
                                pacman->pushSpecialStack( newDir, nextCross );
                            }
                        }
                    }
                }
            }
        }
    }
}

void Engine::render(SDL_Renderer* &renderer) {
    SDL_Rect dsRect;
    ++pacmanFrame; ++ghostFrame;
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 31; ++j) {
            dsRect = {i * 16, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);
        }
    }

    int dir = 0;
    if (!pacman->emptyDirStack()) dir = pacman->getDir();
    objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir, pacmanFrame);

    objectTexture->renderGhostTexture(renderer, blinky->getPosX(), blinky->getPosY(), TextureSrc::BLINKY, blinky->getGhostDir(), ghostFrame);
    objectTexture->renderGhostTexture(renderer,  pinky->getPosX(),  pinky->getPosY(), TextureSrc::PINKY , pinky->getGhostDir() , ghostFrame);
    objectTexture->renderGhostTexture(renderer,   inky->getPosX(),   inky->getPosY(), TextureSrc::INKY  , inky->getGhostDir()  , ghostFrame);
    objectTexture->renderGhostTexture(renderer,  clyde->getPosX(),  clyde->getPosY(), TextureSrc::CLYDE , clyde->getGhostDir() , ghostFrame);
}


void Engine::loop() {
    int pacmanTileX = pacman->getTileX();
    int pacmanTileY = pacman->getTileY();
    int pacmanPosX = pacman->getPosX();
    int pacmanPosY = pacman->getPosY();
    int lastDir = 0;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();
    //cout << lastDir << endl;

    if (!pacman->isDead() && lastDir != 0) {
        if (pacmanTileX * 16 == pacmanPosX && pacmanTileY * 16 == pacmanPosY) {
            if (map->iscrossRoad(pacmanTileX, pacmanTileY)) {
                if (!pacman->emptySpecial()) pacman->turn();
            }
            if (map->canChangeDir(pacmanTileX, pacmanTileY, pacman->getDir())) pacman->moving();
            else pacman->stopmoving();
        }
        else {
            if (map->canChangeDir(pacmanTileX, pacmanTileY, lastDir)) pacman->moving();
            else {
                if (pacmanTileX * 16 == pacmanPosX && pacmanTileY * 16 != pacmanPosY) pacman->moving();
                else if (pacmanTileX * 16 != pacmanPosX && pacmanTileY * 16 == pacmanPosY) pacman->moving();
                else pacman->stopmoving();
            }
        }
    }

    pacmanTileX = pacman->getTileX();
    pacmanTileY = pacman->getTileY();
    int typeOfCoin = map->eatCoins(pacmanTileX, pacmanTileY);
    /*
    if (typeOfCoin != Map::notCoin) {
        pacman->eatCoins();
        if (typeOfCoin == Map::superCoins) {
            blinky->setFrighten(true);
            pinky ->setFrighten(true);
            inky  ->setFrighten(true);
            clyde ->setFrighten(true);
        }
    }
    */

    pacmanPosX = pacman->getPosX();
    pacmanPosY = pacman->getPosY();
    lastDir = 0;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (!pacman->isDead()) {
        if (!blinky->isFrighten())
            blinky->setDestination(pacmanTileX, pacmanTileY);

        if (!pinky->isFrighten()) {
            //if (lastDir == 0) pinky->setDestination(pacmanTileX, pacmanTileY);
            //else {
                switch (lastDir) {
                    case Map::UP:
                        pinky->setDestination(pacmanTileX, pacmanTileY - 4);
                        break;
                    case Map::DOWN:
                        pinky->setDestination(pacmanTileX, pacmanTileY + 4);
                        break;
                    case Map::LEFT:
                        pinky->setDestination(pacmanTileX - 4, pacmanTileY);
                        break;
                    case Map::RIGHT:
                        pinky->setDestination(pacmanTileX + 4, pacmanTileY);
                        break;
                }
           // }
        }
        if (!inky->isFrighten())
            inky->setDestination(2 * pacmanTileX - blinky->getTileX(), 2 * pacmanTileY - blinky->getTileY());

        if (!clyde->isFrighten()) {
            if ((pacmanTileX - clyde->getTileX()) * (pacmanTileX - clyde->getTileX()) + (pacmanTileY - clyde->getTileY()) * (pacmanTileY - clyde->getTileY()) <= 64)
                clyde->setDestination(Ghost::DEFAULT_CLYDE_TILE_X, Ghost::DEFAULT_CLYDE_TILE_Y);
            else
                clyde->setDestination(pacmanTileX, pacmanTileY);
        }
    }
    ghostMove(blinky);
    ghostMove(pinky);
    ghostMove(inky);
    ghostMove(clyde);

    pacman->goThroughTunnel();
    blinky->goThroughTunnel();
    pinky ->goThroughTunnel();
    inky  ->goThroughTunnel();
    clyde ->goThroughTunnel();

}

void Engine::ghostMove(Ghost* &ghost) {
    int ghostTileX = ghost->getTileX();
    int ghostTileY = ghost->getTileY();
    int ghostPosX  = ghost->getPosX();
    int ghostPosY  = ghost->getPosY();
    int ghostOldDir = ghost->getGhostDir();
    int ghostNextTileX = ghost->getNextTileX();
    int ghostNextTileY = ghost->getNextTileY();

    if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
        if (map->iscrossRoad(ghostTileX, ghostTileY)) {
            int distanceUP, distanceDOWN, distanceLEFT, distanceRIGHT;
            distanceUP = distanceDOWN = distanceLEFT = distanceRIGHT = __INT32_MAX__;

            if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP))
                distanceUP = (ghostTileX - ghostNextTileX) * (ghostTileX - ghostNextTileX) + (ghostTileY - 1 - ghostNextTileY) * (ghostTileY - 1 - ghostNextTileY);

            if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN))
                distanceDOWN = (ghostTileX - ghostNextTileX) * (ghostTileX - ghostNextTileX) + (ghostTileY + 1 - ghostNextTileY) * (ghostTileY + 1 - ghostNextTileY);

            if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT))
                distanceLEFT = (ghostTileX - 1 - ghostNextTileX) * (ghostTileX - 1 - ghostNextTileX) + (ghostTileY - ghostNextTileY) * (ghostTileY - ghostNextTileY);

            if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT))
                distanceRIGHT = (ghostTileX + 1 - ghostNextTileX) * (ghostTileX + 1 - ghostNextTileX) + (ghostTileY - ghostNextTileY) * (ghostTileY - ghostNextTileY);

            int distanceMIN;
            if (ghostOldDir == Map::UP) {
                distanceMIN = std::min(distanceUP, std::min(distanceLEFT, distanceRIGHT));
                if (distanceMIN == distanceUP) ghost->setDir(Map::UP);
                else if (distanceMIN == distanceLEFT) ghost->setDir(Map::LEFT);
                else ghost->setDir(Map::RIGHT);
            }
            if (ghostOldDir == Map::DOWN) {
                distanceMIN = std::min(distanceDOWN, std::min(distanceLEFT, distanceRIGHT));
                if (distanceMIN == distanceDOWN) ghost->setDir(Map::DOWN);
                else if (distanceMIN == distanceLEFT) ghost->setDir(Map::LEFT);
                else ghost->setDir(Map::RIGHT);
            }
            if (ghostOldDir == Map::LEFT) {
                distanceMIN = std::min(distanceUP, std::min(distanceDOWN, distanceLEFT));
                if (distanceMIN == distanceUP) ghost->setDir(Map::UP);
                else if (distanceMIN == distanceDOWN) ghost->setDir(Map::DOWN);
                else ghost->setDir(Map::LEFT);
            }
            if (ghostOldDir == Map::RIGHT) {
                distanceMIN = std::min(distanceUP, std::min(distanceRIGHT, distanceDOWN));
                if (distanceMIN == distanceUP) ghost->setDir(Map::UP);
                else if (distanceMIN == distanceRIGHT) ghost->setDir(Map::RIGHT);
                else ghost->setDir(Map::DOWN);
            }

        }
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
    }
    else {
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
        else {
            if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 != ghostPosY && ghost->getGhostDir() % 2 == 1) ghost->moving();
            else if (ghostTileY * 16 == ghostPosY && ghostTileX * 16 != ghostPosX && ghost->getGhostDir() % 2 == 0) ghost->moving();
        }
    }
}
