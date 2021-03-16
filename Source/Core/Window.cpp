#include "Window.h"
#include "../Manager/LogStatus.h"

Window::Window() {
    window = nullptr;
    renderer = nullptr;
    engine = nullptr;
    menu = nullptr;
}

Window::~Window() {
    delete engine;
    engine = nullptr;

    delete menu;
    menu = nullptr;

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

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

            if (TTF_Init() < 0) Console->Status( TTF_GetError() );
            else Console->Status("TTF Ready!");
        }
    }
}

void Window::quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    TTF_Quit();
    atexit(SDL_Quit);
    Console->Status("Successfully exited!");
    return;
}

void Window::runGame() {
    menu = new Menu();
    menu->init(renderer);

    engine = new Engine();
    engine->init(renderer);
    SDL_Event e;

    while (Running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) Running = false;
            else {
                switch (menu->getStatus()) {
                    case Menu::RUNNING:
                        menu->handleEvent(e, renderer);
                        break;
                    case Menu::EXIT_BUTTON_PRESSED:
                        Running = false;
                        break;
                    case Menu::PLAY_BUTTON_PRESSED:
                        engine->handleEvent(e);
                        break;
                }

            }
        }
        if (menu->getStatus() == Menu::PLAY_BUTTON_PRESSED) engine->loop();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (menu->getStatus()) {
            case Menu::RUNNING:
                menu->render(renderer); break;
            case Menu::PLAY_BUTTON_PRESSED:
                engine->render(renderer); break;
        }

        SDL_RenderPresent(renderer);
    }
}
