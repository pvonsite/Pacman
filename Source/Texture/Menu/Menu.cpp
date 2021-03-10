#include "Menu.h"

Menu::Menu() {
    menuTexture = nullptr;
}

Menu::~Menu() {
    SDL_DestroyTexture(menuTexture);
    menuTexture = nullptr;
}

void Menu::init(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("Pacman Menu Background.jpg");
    if (Image == nullptr) {
        console->Status( IMG_GetError() );
    }
    else {
        menuTexture = SDL_CreateTextureFromSurface(renderer, Image);

    }
}

void Menu::render(SDL_Renderer* &renderer) {
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
}
