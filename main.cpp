#include "Window.h"

int main(int argc, char* argv[]) {

    Window* window = new Window();

    window->initSDL();

    window->runGame();

    window->quitSDL();
    return 0;
}
