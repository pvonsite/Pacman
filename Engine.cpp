#include "Engine.h"

void Engine::init(SDL_Renderer* &renderer) {
    map = new Map();
    pacman = new Pacman();
    objectTexture = new TextureSrc();
    objectTexture->loadTileTexture(renderer);
    objectTexture->loadPacmanTexture(renderer);
}

void Engine::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {

            int velX = 0, velY = 0, dir = 1;

            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    velY = -Pacman::pacmanVelocity; dir = 1; break;
                case SDLK_DOWN:
                    velY =  Pacman::pacmanVelocity; dir = 3; break;
                case SDLK_RIGHT:
                    velX =  Pacman::pacmanVelocity; dir = 2; break;
                case SDLK_LEFT:
                    velX = -Pacman::pacmanVelocity; dir = 4; break;
            }

            if (pacman->getOldDir() != dir % 2) {
                if (pacman->getPosX() % 16 != 0 || pacman->getPosY() % 16 != 0) return;
            }

            if (!map->isWall( pacman->getNextTileID(dir) ))
               pacman->changeVelocityDir(velX, velY, dir);
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

    std::cout << pacman->getPosX() << " " << pacman->getPosY() << std::endl;
    objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), 1);
}

void Engine::loop() {

    if (!map->isWall( pacman->getNextTileID() )) {
        pacman->manageMove();
        pacman->move();
    }
    //else pacman->stop();
}
