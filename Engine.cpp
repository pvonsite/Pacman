#include "Engine.h"

typedef std::pair<int, int> II;
typedef std::pair<int, std::pair<int, int> > IP;

void Engine::init(SDL_Renderer* &renderer) {
    map = new Map();
    map->findingCrossRoad();
    map->NextCrossTileID();
    pacman = new Pacman();
    objectTexture = new TextureSrc();
    objectTexture->loadTileTexture(renderer);
    objectTexture->loadPacmanTexture(renderer);
    pacman->pushtoStack(1);
}

void Engine::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
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
            }

            if (lastDir == 0) {
                if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
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
                            else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 30) {
                                pacman->pushSpecialStack( newDir, nextCross );
                            }
                        }
                    }
                    else if (lastDir % 2 == 1 && newDir % 2 == 0) {
                        if (pacmanPosX == pacmanTileX * 16) {
                            if (map->canChangeDir(pacmanTileX, pacmanTileY, newDir)) {
                                    pacman->pushSpecialStack(newDir, II(pacmanTileX, pacmanTileY));
                            }
                            else if (nextCross != II(-1, -1) && !map->besideCrossIsWall(nextCross, newDir) && abs(pacmanPosY - nextCross.second * 16) <= 30) {
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
    ++frame;
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 31; ++j) {
            dsRect = {i * 16, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);
        }
    }

    int dir = 0;
    if (!pacman->emptyDirStack()) dir = pacman->getDir();
    objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir, frame);
}


void Engine::loop() {
    int pacmanTileX = pacman->getTileX();
    int pacmanTileY = pacman->getTileY();
    int lastDir = 0;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (lastDir != 0) {
        if (!pacman->emptySpecial() ) {
            II nextCross = pacman->getSpecial();

            if (nextCross != II(-1, -1)) {
                if (pacman->getPosX() == nextCross.first * 16 && pacman->getPosY() != nextCross.second * 16) pacman->moving();
                else if (pacman->getPosX() != nextCross.first * 16 && pacman->getPosY() == nextCross.second * 16) pacman->moving();
                else if (pacman->getPosX() == nextCross.first * 16 && pacman->getPosY() == nextCross.second * 16) pacman->turn();
            }
        }
        else if (map->canChangeDir(pacmanTileX, pacmanTileY, lastDir)) pacman->moving();
        else {
            if (pacmanTileX * 16 == pacman->getPosX() && pacmanTileY * 16 != pacman->getPosY() && lastDir % 2 == 1) pacman->moving();
            else if (pacmanTileX * 16 != pacman->getPosX() && pacmanTileY * 16 == pacman->getPosY() && lastDir % 2 == 0) pacman->moving();
            else pacman->stopmoving();
        }
    }

    if (map->eatCoins(pacmanTileX, pacmanTileY)) pacman->eatCoins();
}
