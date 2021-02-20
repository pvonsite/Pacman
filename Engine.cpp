#include "Engine.h"

void Engine::init(SDL_Renderer* &renderer) {
    map = new Map();
    objectTexture = new TextureSrc();
    objectTexture->loadTileTexture(renderer);
}

void Engine::handleEvent(SDL_Event &e) {

}

void Engine::render(SDL_Renderer* &renderer) {
    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 31; ++j) {
            SDL_Rect dsRect = {i * 16, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getTileID(i, j), &dsRect);
        }
    }
}
