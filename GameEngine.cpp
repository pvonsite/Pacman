#include "GameEngine.h"
#include "Log.h"

using namespace std;

Log engineLog("Game Engine:");

SDL_Window* GameEngine::window;
SDL_Renderer* GameEngine::renderer;

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
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IMG_Init(IMG_INIT_PNG) < 0) {
                engineLog.Status( IMG_GetError() );
            }

            if (TTF_Init() < 0) {
                engineLog.Status( TTF_GetError() );
            }
        }
    }
}

void GameEngine :: quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
