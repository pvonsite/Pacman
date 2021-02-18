#include "GameEngine.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    GameEngine::initSDL();

    while (GameEngine::getRunStatus()) {
        GameEngine::handleEvent();
    }

    GameEngine::quitSDL();
    return 0;
}
