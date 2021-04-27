#include "Window.h"
#include "../Manager/LogStatus.h"

Window::Window() {
    window = nullptr;
    renderer = nullptr;
    playState = nullptr;
    startMenu = nullptr;
    runningMenu = false;
}

Window::~Window() {
    delete playState;
    playState = nullptr;

    delete startMenu;
    startMenu = nullptr;

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

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) Console->Status( Mix_GetError() );
            else Console->Status("Audio Ready!");
            Mix_Volume(-1, MIX_MAX_VOLUME);

            freopen("score.txt", "r", stdin);
            std::string t = "";
            for (int i = 0; i < 10; ++i) {
                std::getline(std::cin, t);
                highScore.push_back(t);
            }
        }
    }
}

void Window::quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    Mix_Quit();
    TTF_Quit();
    atexit(SDL_Quit);
    Console->Status("Successfully exited!");
    freopen("score.txt", "w", stdout);
    for (int i = 0; i < 10; ++i) std::cout << highScore[i] << std::endl;
    return;
}

void Window::runGame() {
    startMenu = new Menu(262, 170, startMenuButtonText.size(), 320, 30);
    startMenu->init(renderer, "Source/Assets/Menu Image/Pacman Pause Menu.png", startMenuButtonText);
    startMenu->changeRunStatus();

    SDL_Event e;
    runningMenu = true;
    bool startGame = false;

    while (Running) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) Running = false;
            else {
                if (runningMenu) {
                    startMenu->handleEvent(e, renderer);
                    switch (startMenu->getStatus()) {
                        case Menu::PLAY_BUTTON_PRESSED:
                            runningMenu = false; break;
                        case Menu::EXIT_BUTTON_PRESSED:
                            Running = false; break;
                    }
                }
                else {
                    playState->handleEvent(e, renderer, runningMenu, highScore);
                    if (runningMenu) startMenu->reOpen();
                }
            }
        }
        if (!runningMenu) {
            if (!startGame) {
                playState = new PlayStateManager();
                playState->newGame(renderer);
                startGame = true;
            }
            playState->runGame(runningMenu);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (runningMenu)
            startMenu->render(renderer, highScore);
        else playState->render(renderer, highScore);

        SDL_RenderPresent(renderer);
    }
}
