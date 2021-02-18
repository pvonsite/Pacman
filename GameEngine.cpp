#include "GameEngine.h"

using namespace std;

Log engineLog("Game Engine:");

//SDL_Window* GameEngine::window;
//SDL_Renderer* GameEngine::renderer;

void GameEngine :: initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        cout << "SDL could not initialize! " << SDL_GetError();
    else {
        window = SDL_CreateWindow(Window_Tittle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
            cout << "Window could not be created! " << SDL_GetError();
        else {
            //#ifdef ENVIROMRENT
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            //#elif
                //renderer = SDL_CreateSoftwareRenderer(screenSurface);
            //#endif // ENVIROMRENT

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (TTF_Init() < 0) {
                cout << "Error: " << TTF_GetError();
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
    SDL_Quit();
}
