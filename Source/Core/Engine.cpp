#include "Engine.h"
#include <limits>
#include <random>
#include <time.h>

using namespace std;

typedef std::pair<int, int> II;
typedef std::pair<int, std::pair<int, int> > IP;

void Engine::init(SDL_Renderer* &renderer) {
    /// initialize map
    map = new Map();
    /// initialize object
    objectTexture = new TextureSrc();
    objectTexture->loadTileTexture(renderer);
    objectTexture->loadPacmanAndGhostTexture(renderer);
    /// tick, gameplay manager
    tickManager = new TickManager();
    gameManager = new GameManager(renderer);
    soundManager = new SoundManager();
    soundManager->loadSound();
    srand(time(nullptr));
    apple = new Item(renderer, "Source/Assets/Entity Image/greenapple.png");
    newGame();
    SDL_Surface* Image = IMG_Load("Source/Assets/Menu Image/nextlevel.png");
    nextLevel = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    Image = IMG_Load("Source/Assets/Menu Image/ready.png");
    ready = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
}

void Engine::newGame() {
    map->reset();
    gameManager->reset();
    delete pacman;
    pacman = new Pacman();
    delete blinky;
    if (gameManager->getLevel() < 5)
        blinky = new Ghost(13, 11, false);
    else
        blinky = new Ghost(12, 11, false);
    delete pinky;
    pinky  = new Ghost(13, 14, true);
    delete inky;
    inky   = new Ghost(11, 14, true);
    delete clyde;
    clyde  = new Ghost(15, 14, true);
    if (gameManager->getLevel() >= 3) {
        apple->spawnAt(1, 1);
        delete greendy;
        greendy = new Ghost(12, 15, true);
    }
    if (gameManager->getLevel() >= 5) {
        delete friendy;
        friendy = new Ghost(14, 11, false);
    }
    soundManager->insertPlayList(SoundManager::START);
    tickManager->resetTick(gameManager->getLevel());
    tickManager->pauseTick(true);
    runningEGBoard = false;
}

void Engine::respawnObject() {
    delete pacman;
    pacman = new Pacman();
    //pacman->respawn();
    soundManager->reset();
    delete blinky;
    blinky = new Ghost(13, 11, false);
    delete pinky;
    pinky  = new Ghost(13, 14, true);
    delete inky;
    inky   = new Ghost(11, 14, true);
    delete clyde;
    clyde  = new Ghost(15, 14, true);
    if (greendy != nullptr) {
        delete greendy;
        greendy = new Ghost(12, 15, true);
    }
    if (friendy != nullptr) {
        delete friendy;
        friendy = new Ghost(14, 11, false);
    }
    tickManager->pauseTick(false);
}

void Engine::handleEvent(SDL_Event &e, std::vector<std::string> &scoreData) {
    if (Mix_Playing(2) || Mix_Playing(4)) return;
    if (pacman->isDead()) {
        if (runningEGBoard) gameManager->handleEGBoard(e, scoreData);
        return;
    }
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT
         || e.key.keysym.sym == SDLK_s    || e.key.keysym.sym == SDLK_w  || e.key.keysym.sym == SDLK_a    || e.key.keysym.sym == SDLK_d    ) {
            int newDir  = -1;
            int lastDir = -1;
            int pacmanTileX = pacman->getTileX();
            int pacmanTileY = pacman->getTileY();
            int pacmanPosX  = pacman->getPosX();
            int pacmanPosY  = pacman->getPosY();

            if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

            if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) newDir = 0;
            else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) newDir = 1;
            else if (e.key.keysym.sym == SDLK_DOWN  || e.key.keysym.sym == SDLK_s) newDir = 2;
            else if (e.key.keysym.sym == SDLK_LEFT  || e.key.keysym.sym == SDLK_a) newDir = 3;

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

void Engine::render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData) {
    tickManager->stablizeFPS();
    SDL_Rect dsRect;
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 31; ++j) {
            dsRect = {i * 16 + 217, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);
        }
    }
    if (gameManager->getLevel() >= 3 && !apple->isDestroyed()) apple->renderItem(renderer);

    if (!runningEGBoard) {
        int dir = -1;
        if (!pacman->emptyDirStack()) dir = pacman->getDir();
        if (!pacman->isDead()) {
            renderGhost(renderer, blinky, TextureSrc::BLINKY);
            renderGhost(renderer, pinky , TextureSrc::PINKY );
            renderGhost(renderer, inky  , TextureSrc::INKY  );
            renderGhost(renderer, clyde , TextureSrc::CLYDE );
            if (greendy != nullptr) renderGhost(renderer, greendy, TextureSrc::GREENDY);
            if (friendy != nullptr) renderGhost(renderer, friendy, TextureSrc::FRIENDY);
            if (Mix_Playing(2)) {
                dsRect = {441 - 82, 285 - 15 - 7, 164, 30};
                SDL_RenderCopy(renderer, ready, nullptr, &dsRect);
            }
        }
        if (pacman->isDead()) {
            if (objectTexture->pacmanIsDead()) {
                if (gameManager->getRemainLife() > 0) respawnObject();
                else {
                    runningEGBoard = true;
                    gameManager->checkScoreData(scoreData);
                }
            }
            else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), TextureSrc::DEAD_PACMAN);
        }
        else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir);
        if (waitTime > 0) {
            dsRect = {441 - 97, 248 - 52, 194, 104};
            SDL_RenderCopy(renderer, nextLevel, nullptr, &dsRect);
        }
        if (Mix_Playing(4)) {
            objectTexture->renderGhostScore(renderer, gameManager->getEatenGhostPosX(), gameManager->getEatenGhostPosY(), gameManager->getEatenGhostStreak());
        }
        soundManager->playSound();
    }

    if (runningEGBoard) gameManager->runEGBoard(renderer);
    else gameManager->renderHUD(renderer);
}


void Engine::loop(bool &exitToMenu) {
    if (gameManager->clearAllCoins()) {
        if (waitTime > 0) --waitTime;
        else {
            gameManager->nextLevel();
            tickManager->resetTick(gameManager->getLevel());
            respawnObject();
            map->reset();
        }
        return;
    }
    if (Mix_Playing(2) || Mix_Playing(4)) {
        if (Mix_Playing(2)) tickManager->pauseTick(true);
        return;
    }
    if (pacman->isDead()) {
        if (runningEGBoard) {
            cout << gameManager->getPlayerDecision() << endl;
            switch (gameManager->getPlayerDecision()) {
                case GameManager::AGAIN:
                    newGame();
                    break;
                case GameManager::QUIT:
                    exitToMenu = true; break;
            }
        }
        return;
    }
    tickManager->updateStatus();
    int pacmanTileX = pacman->getTileX();
    int pacmanTileY = pacman->getTileY();
    int pacmanPosX = pacman->getPosX();
    int pacmanPosY = pacman->getPosY();
    int lastDir = -1;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (!pacman->isDead() && lastDir != -1) {
        if (pacmanTileX * 16 == pacmanPosX && pacmanTileY * 16 == pacmanPosY) {
            if (map->iscrossRoad(pacmanTileX, pacmanTileY)) {
                if (!pacman->emptySpecial() && pacman->getSpecial() == II(pacmanTileX, pacmanTileY)) pacman->turn();
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
    int remainCoin = gameManager->getRemainCoin();
    if (remainCoin < 50) soundManager->insertPlayList(SoundManager::MOVE_3);
    else if (remainCoin < 100) soundManager->insertPlayList(SoundManager::MOVE_2);
    else if (remainCoin < 150) soundManager->insertPlayList(SoundManager::MOVE_1);
    else soundManager->insertPlayList(SoundManager::MOVE_0);

    pacmanTileX = pacman->getTileX();
    pacmanTileY = pacman->getTileY();
    int typeOfCoin = map->eatCoins(pacmanTileX, pacmanTileY);

    if (typeOfCoin != GameManager::notCoin) {
        gameManager->eatCoins(typeOfCoin);
        soundManager->insertPlayList(SoundManager::EAT_DOT);
        if (typeOfCoin == GameManager::superCoin) {
            tickManager->setFrightenTime();
            soundManager->insertPlayList(SoundManager::GHOST_TURN_BLUE);
            if (!blinky->isDead()) blinky->setFrighten(true);
            if (!pinky ->isDead()) pinky ->setFrighten(true);
            if (!inky  ->isDead()) inky  ->setFrighten(true);
            if (!clyde ->isDead()) clyde ->setFrighten(true);
            if (greendy != nullptr) {
                if (!greendy->isDead()) greendy->setFrighten(true);
            }
            if (friendy != nullptr) tickManager->friendyStartChasePacman();
        }
    }
    if (!tickManager->isFrightenTime()) {
        soundManager->insertPlayList(SoundManager::NORMAL_GHOST);
        blinky->setFrighten(false);
        pinky ->setFrighten(false);
        inky  ->setFrighten(false);
        clyde ->setFrighten(false);
        if (greendy != nullptr) greendy->setFrighten(false);
    }
    bool scatter = tickManager->isScatteringTime();
    blinky->setScattering(scatter);
    pinky ->setScattering(scatter);
    inky  ->setScattering(scatter);
    clyde ->setScattering(scatter);
    if (!tickManager->isGreendyChaseTime()) {
        eatGreenApple = false;
    }
    else {
        if (apple->isDestroyed()) {
            switch (rand() % 4) {
                case 0: apple->spawnAt(1, 1); break;
                case 1: apple->spawnAt(26, 1); break;
                case 2: apple->spawnAt(26, 29); break;
                case 3: apple->spawnAt(1, 29); break;
            }
        }
    }

    pacmanPosX = pacman->getPosX();
    pacmanPosY = pacman->getPosY();
    lastDir = -1;
    if (!pacman->emptyDirStack()) lastDir = pacman->getDir();

    if (!pacman->isDead()) {
        tickManager->pauseTick(false);
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

        if (greendy != nullptr) {
            if (greendy->isDead())
                greendy->setDestination(13, 11);
            else if (eatGreenApple == false)
                greendy->setDestination(apple->getPosX(), apple->getPosY());
            else if (!greendy->isFrighten())
                greendy->setDestination(pacmanTileX, pacmanTileY, 2);
        }
        if (friendy != nullptr && tickManager->isFriendyChaseTime()) {
            friendy->setDestination(pacmanTileX, pacmanTileY, 1);
        }
    }
    pacman->goThroughTunnel();
    ghostMove(blinky);
    ghostMove(pinky);
    ghostMove(inky);
    ghostMove(clyde);
    ghostMove(greendy);
    ghostMove(friendy);

    gameManager->handleGhostPos(pinky, inky, clyde, greendy);

    if (gameManager->clearAllCoins()) {
        soundManager->insertPlayList(SoundManager::WINNING);
        waitTime = 100;
    }
}

void Engine::ghostMove(Ghost* &ghost) {
    if (ghost == nullptr) return;
    int ghostTileX = ghost->getTileX();
    int ghostTileY = ghost->getTileY();
    int ghostPosX  = ghost->getPosX();
    int ghostPosY  = ghost->getPosY();
    int ghostOldDir = ghost->getGhostDir();
    int ghostNextTileX = ghost->getNextTileX();
    int ghostNextTileY = ghost->getNextTileY();

    if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
        if (map->iscrossRoad(ghostTileX, ghostTileY)) {
            if (ghost->isFrighten() || (ghost == friendy && !tickManager->isFriendyChaseTime())) {
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
                    distanceUP = map->getDist(II(ghostTileX, ghostTileY - 1), II(ghostNextTileX, ghostNextTileY), Map::UP);

                if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN))
                    distanceDOWN = map->getDist(II(ghostTileX, ghostTileY + 1), II(ghostNextTileX, ghostNextTileY), Map::DOWN);

                if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT))
                    distanceLEFT = map->getDist(II(ghostTileX - 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::LEFT);

                if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT))
                    distanceRIGHT = map->getDist(II(ghostTileX + 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::RIGHT);

                int distanceMIN;
                if (ghostOldDir == Map::UP) {
                    distanceMIN = std::min(distanceUP, std::min(distanceLEFT, distanceRIGHT));
                    if (distanceMIN == distanceUP) ghost->setDir(Map::UP);
                    else if (distanceMIN == distanceLEFT) ghost->setDir(Map::LEFT);
                    else ghost->setDir(Map::RIGHT);
                }
                else if (ghostOldDir == Map::DOWN) {
                    distanceMIN = std::min(distanceDOWN, std::min(distanceLEFT, distanceRIGHT));
                    if (distanceMIN == distanceDOWN) ghost->setDir(Map::DOWN);
                    else if (distanceMIN == distanceLEFT) ghost->setDir(Map::LEFT);
                    else ghost->setDir(Map::RIGHT);
                }
                else if (ghostOldDir == Map::LEFT) {
                    distanceMIN = std::min(distanceUP, std::min(distanceDOWN, distanceLEFT));
                    if (distanceMIN == distanceUP) ghost->setDir(Map::UP);
                    else if (distanceMIN == distanceDOWN) ghost->setDir(Map::DOWN);
                    else ghost->setDir(Map::LEFT);
                }
                else if (ghostOldDir == Map::RIGHT) {
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
    ghost->goThroughTunnel();
    if (ghostPosX == ghostNextTileX * 16 && ghostPosY == ghostNextTileY * 16) {
        if (ghost->isDead()) {
            ghost->setDead(false);
            soundManager->insertPlayList(SoundManager::REVIVAL_GHOST);
        }
        else {
            if (ghost == greendy) {
                tickManager->greendyStartChasePacman();
                ghost->resetObjectTile(ghostTileX, ghostTileY);
                apple->destroyItem();
                eatGreenApple = true;
            }
        }
    }
    pacmanMeatGhost(ghost);
}

void Engine::pacmanMeatGhost(Ghost* &ghost) {
    if (ghost->isDead()) return;
    int distance = (pacman->getPosX() - ghost->getPosX()) * (pacman->getPosX() - ghost->getPosX()) + (pacman->getPosY() - ghost->getPosY()) * (pacman->getPosY() - ghost->getPosY());
    if (distance <= 9) {
    //if ((pacman->getPosX() == ghost->getPosX() && abs(pacman->getPosY() - ghost->getPosY()) <= 3) ||
    //    (pacman->getPosY() == ghost->getPosY() && abs(pacman->getPosX() - ghost->getPosX()) <= 3)) {
        if (ghost->isFrighten()) {
            gameManager->eatGhost(ghost->getPosX(), ghost->getPosY());
            ghost->setDead(true);
            ghost->setFrighten(false);
            soundManager->insertPlayList(SoundManager::EAT_GHOST);
            soundManager->insertPlayList(SoundManager::GHOST_GO_HOME);
        }
        else {
            pacman->setDead(true, 1);
            gameManager->lostALife();
            soundManager->insertPlayList(SoundManager::DEAD);
            tickManager->pauseTick(true);
        }
    }
}

void Engine::renderGhost(SDL_Renderer* &renderer, Ghost* &ghost, int ghostID) {
    if (ghost == nullptr) return;
    if (ghost->isDead())
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), TextureSrc::GHOST_SPIRIT, ghost->getGhostDir());
    else if (ghost->isFrighten()) {
        if (tickManager->remainFrightenTime() < 2.0)
            objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN_GHOST_2);
        else
            objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN_GHOST_1);
    }
    else
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, ghost->getGhostDir());
}
