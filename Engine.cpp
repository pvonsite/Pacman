#include "Engine.h"
#include <limits>
#include <random>
#include <time.h>

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
    tickManager = new TickManager();
    tickManager->resetTick();
    //blinky->setDir(Map::LEFT);
    //pinky->setDir(Map::UP);
    srand(time(nullptr));
}

void Engine::revivalPacman() {
    pacman->respawn();
    delete blinky;
    blinky = new Ghost(13, 11);
    delete pinky;
    pinky  = new Ghost(13, 11);
    delete inky;
    inky   = new Ghost(11, 11);
    delete clyde;
    clyde  = new Ghost(15, 11);
}

void Engine::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT
         || e.key.keysym.sym == SDLK_s    || e.key.keysym.sym == SDLK_w  || e.key.keysym.sym == SDLK_a    || e.key.keysym.sym == SDLK_d    ) {
            int newDir  = -1;
            int lastDir = -1;
            int pacmanTileX = pacman->getTileX();
            int pacmanTileY = pacman->getTileY();
            int pacmanPosX  = pacman->getPosX();
            int pacmanPosY  = pacman->getPosY();
            if (pacman->isDead()) return;

            if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

            switch (e.key.keysym.sym) {
                case SDLK_UP   : newDir = 0; break;
                case SDLK_DOWN : newDir = 2; break;
                case SDLK_LEFT : newDir = 3; break;
                case SDLK_RIGHT: newDir = 1; break;
                case SDLK_w    : newDir = 0; break;
                case SDLK_s    : newDir = 2; break;
                case SDLK_a    : newDir = 3; break;
                case SDLK_d    : newDir = 1; break;
            }

            if (lastDir == -1) {
                if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                    pacman->eraseSpecial();
                    pacman->pushtoStack(newDir);
                }
            }
            else {
                if (newDir % 2 == lastDir % 2) {
                    if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                        pacman->pushtoStack(newDir);
                        pacman->eraseSpecial();
                    }
                }
                else {
                    std::pair<int, int> nextCross = map->getnextCrossID(pacmanTileX, pacmanTileY, lastDir);

                    if (lastDir % 2 == 1 && newDir % 2 == 0) {
                        if (pacmanPosY == pacmanTileY * 16) {
                            if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                                    pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
                            }
                            else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 32) {
                                pacman->pushSpecialStack( newDir, nextCross );
                            }
                        }
                    }
                    else if (lastDir % 2 == 0 && newDir % 2 == 1) {
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
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 31; ++j) {
            dsRect = {i * 16, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);
        }
    }

    int dir = -1;
    if (!pacman->emptyDirStack()) dir = pacman->getDir();
    if (pacman->isDead()) {
        if (objectTexture->pacmanIsDead()) {
            if (pacman->getLife()) revivalPacman();
            else init(renderer);
        }
        else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), TextureSrc::DEAD_PACMAN);
    }
    else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir);


    if (!pacman->isDead()) {
        renderGhost(renderer, blinky, TextureSrc::BLINKY);
        renderGhost(renderer, pinky , TextureSrc::PINKY );
        renderGhost(renderer, inky  , TextureSrc::INKY  );
        renderGhost(renderer, clyde , TextureSrc::CLYDE );
    }
}


void Engine::loop() {
    tickManager->updateStatus();

    if (pacman->isDead()) return;
    int pacmanTileX = pacman->getTileX();
    int pacmanTileY = pacman->getTileY();
    int pacmanPosX = pacman->getPosX();
    int pacmanPosY = pacman->getPosY();
    int lastDir = -1;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (!pacman->isDead() && lastDir != -1) {
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

    if (typeOfCoin != Map::notCoin) {
        pacman->eatCoins();
        if (typeOfCoin == Map::superCoins) {
            tickManager->setStatus(TickManager::FRIGHTEN_MODE);
            blinky->setFrighten(true); blinky->setDir((blinky->getGhostDir() + 2) % 4);
            pinky ->setFrighten(true); pinky ->setDir((pinky ->getGhostDir() + 2) % 4);
            inky  ->setFrighten(true); inky  ->setDir((inky  ->getGhostDir() + 2) % 4);
            clyde ->setFrighten(true); clyde ->setDir((clyde ->getGhostDir() + 2) % 4);
        }
    }

    if (tickManager->getStatus() == TickManager::SCATTERING_MODE) {
        blinky->setScattering(true);
        pinky->setScattering(true);
        inky->setScattering(true);
        clyde->setScattering(true);
    }
    else {
        blinky->setScattering(false);
        pinky->setScattering(false);
        inky->setScattering(false);
        clyde->setScattering(false);
    }

    pacmanPosX = pacman->getPosX();
    pacmanPosY = pacman->getPosY();
    lastDir = -1;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (!pacman->isDead()) {
        if (blinky->isDead())
            blinky->setDestination(13, 11);
        else if (!blinky->isScattering())
            blinky->setDestination(pacmanTileX, pacmanTileY);
        else blinky->setDestination(Ghost::DEFAULT_BLINKY_TILE_X, Ghost::DEFAULT_BLINKY_TILE_Y);

        if (pinky->isDead())
            pinky->setDestination(13, 11);
        else if (!pinky->isScattering()) {
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
        }
        else pinky->setDestination(Ghost::DEFAULT_PINKY_TILE_X, Ghost::DEFAULT_PINKY_TILE_Y);

        if (inky->isDead())
            inky->setDestination(13, 11);
        else if (!inky->isScattering())
            inky->setDestination(2 * pacmanTileX - blinky->getTileX(), 2 * pacmanTileY - blinky->getTileY());
        else inky->setDestination(Ghost::DEFAULT_INKY_TILE_X, Ghost::DEFAULT_INKY_TILE_Y);

        if (clyde->isDead())
            clyde->setDestination(13, 11);
        else if (!clyde->isScattering()) {
            if ((pacmanTileX - clyde->getTileX()) * (pacmanTileX - clyde->getTileX()) + (pacmanTileY - clyde->getTileY()) * (pacmanTileY - clyde->getTileY()) <= 64)
                clyde->setDestination(Ghost::DEFAULT_CLYDE_TILE_X, Ghost::DEFAULT_CLYDE_TILE_Y);
            else
                clyde->setDestination(pacmanTileX, pacmanTileY);
        }
        else clyde->setDestination(Ghost::DEFAULT_CLYDE_TILE_X, Ghost::DEFAULT_CLYDE_TILE_Y);
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

    pacmanMeatGhost(blinky);
    pacmanMeatGhost(pinky);
    pacmanMeatGhost(inky);
    pacmanMeatGhost(clyde);
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
            if (ghost->isFrighten()) {
                std::stack<int> whichDir;
                if (ghostOldDir % 2 == 1) {
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP)) whichDir.push(0);
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN)) whichDir.push(2);
                    if (map->canChangeDir(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir);
                }
                else {
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT)) whichDir.push(3);
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT)) whichDir.push(1);
                    if (map->canChangeDir(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir);
                }
                int dir = rand() % (int) whichDir.size() + 1;
                while (dir > 1) whichDir.pop(), --dir;
                ghost->setDir(whichDir.top());
                while (!whichDir.empty()) whichDir.pop();
            }
            else {
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
        }
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
    }
    else {
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving();
        else {
            if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 != ghostPosY && ghost->getGhostDir() % 2 == 0) ghost->moving();
            else if (ghostTileY * 16 == ghostPosY && ghostTileX * 16 != ghostPosX && ghost->getGhostDir() % 2 == 1) ghost->moving();
        }
    }
    if (ghost->isDead() && ghostPosX == ghostNextTileX * 16 && ghostPosY == ghostNextTileY * 16) {
        ghost->setDead(false);
    }
}

void Engine::pacmanMeatGhost(Ghost* &ghost) {
    if (ghost->isDead()) return;
    if ((pacman->getPosX() == ghost->getPosX() && abs(pacman->getPosY() - ghost->getPosY()) <= 3) ||
        (pacman->getPosY() == ghost->getPosY() && abs(pacman->getPosX() - ghost->getPosX()) <= 3)) {
        if (ghost->isFrighten()) {
            ghost->setDead(true);
            ghost->setFrighten(false);
        }
        else {
            pacman->setDead(true);
        }
    }
}

void Engine::renderGhost(SDL_Renderer* &renderer, Ghost* &ghost, int ghostID) {
    if (ghost->isDead())
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), TextureSrc::GHOST_SPIRIT, ghost->getGhostDir());
    else if (ghost->isFrighten())
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN_GHOST);
    else
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, ghost->getGhostDir());
}
