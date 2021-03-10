#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include "../Map/Map.h"
#include "../Texture/Entity/TextureSrc.h"
#include "../Object/Pacman.h"
#include "../Object/Ghost.h"
#include "../Manager/TickManager.h"
#include "../Manager/GameManager.h"

class Engine {
    private:
        Map* map;
        Pacman* pacman;
        Ghost* blinky;
        Ghost* pinky;
        Ghost* inky;
        Ghost* clyde;
        TextureSrc* objectTexture;
        TickManager* tickManager;
        GameManager* gameManager;
    public:
        Engine() {
            map = nullptr;
            pacman = nullptr;
            objectTexture = nullptr;
            tickManager = nullptr;
            gameManager = nullptr;
        }

        ~Engine() {
            map = nullptr;
            delete map;

            pacman = nullptr;
            delete pacman;

            objectTexture = nullptr;
            delete objectTexture;

            tickManager = nullptr;
            delete tickManager;

            gameManager = nullptr;
            delete gameManager;
        }

        void respawnObject();

        void init(SDL_Renderer* &renderer);

        void handleEvent(SDL_Event &e);

        void render(SDL_Renderer* &renderer);

        void loop();

        void ghostMove(Ghost* &ghost);

        void pacmanMeatGhost(Ghost* &ghost);

        void renderGhost(SDL_Renderer* &renderer, Ghost* &ghost, int ghostID);
};

#endif // _ENGINE_H_
