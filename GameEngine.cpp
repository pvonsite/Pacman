#include <iostream>
#include "GameEngine.h"

#define ENVIROMRENT "HOME"

using namespace std;

Log engineLog("Game Engine:");

SDL_Window* GameEngine::window;
SDL_Renderer* GameEngine::renderer;
SDL_Event e;

Texture gameTexture;

bool GameEngine::Running = false;


void GameEngine :: initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        engineLog.Status( SDL_GetError() );
    }
    else {
        window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            engineLog.Status( SDL_GetError() );
        }
        else {
            engineLog.Status("Window opend successfully!");

            #ifdef ENVIROMRENT
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            #elif
                renderer = SDL_CreateSoftwareRenderer(screenSurface);
            #endif // ENVIROMRENT

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            GameEngine::Running = true;

            if (IMG_Init(IMG_INIT_PNG) < 0) {
                engineLog.Status( IMG_GetError() );
            }
            else {
                engineLog.Status("IMG loaded successfully!");
            }

            if (TTF_Init() < 0) {
                engineLog.Status( TTF_GetError() );
            }
            else {
                engineLog.Status("TTF loaded successfully!");
            }
        }
    }
    return;
}

void GameEngine :: quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    atexit(SDL_Quit);

    engineLog.Status("Successfully exited!");
    return ;
}

void GameEngine::handleEvent() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            engineLog.Status("Closing ...");
            GameEngine::Running = false;
        }
    }
}

void GameEngine :: initTexture() {
    gameTexture.loadTexture(renderer);
}
