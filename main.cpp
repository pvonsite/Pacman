#include <iostream>
#include "GameEngine.h"

using namespace std;

int main(int argc, char* argv[]) {
    GameEngine newgame;
    newgame.initSDL();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
    }

    newgame.quitSDL();
    //return 0;
}
