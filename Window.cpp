#include "Window.h"
#include "LogStatus.h"

void Window::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Console->Status( SDL_GetError() );
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        Console->Status("Window opened successfully!");
        Running = true;

        if (window == nullptr) {
            Console->Status( SDL_GetError() );
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully!");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }
}

void Window::quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    atexit(SDL_Quit);
    Console->Status("Successfully exited!");
    return;
}

void Window::runGame() {
    SDL_Event e;
    engine = new Engine();
    engine->init(renderer);

    while (Running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) Running = false;
            engine->handleEvent(e);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        engine->render(renderer);

        SDL_RenderPresent(renderer);
    }
}
