#include <iostream>
#include "GameEngine.h"

using namespace std;

int main(int argc, char* argv[]) {
    GameEngine::initSDL();

    SDL_Delay(5000);

    GameEngine::quitSDL();
    return 0;
}
