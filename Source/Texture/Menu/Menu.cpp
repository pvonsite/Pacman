#include "Menu.h"

Menu::Menu() {
    menuTexture = nullptr;
}

Menu::~Menu() {
    SDL_DestroyTexture(menuTexture);
    menuTexture = nullptr;
}

void Menu::init(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("Source/Texture/Menu Image/Pacman Menu Background.jpg");
    if (Image == nullptr) {
        console->Status( IMG_GetError() );
    }
    else {
        menuTexture = SDL_CreateTextureFromSurface(renderer, Image);
        menuButton[0] = new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 441 - MENU_BUTTON_WIDTH / 2, 260 - 5 - MENU_BUTTON_HEIGHT);
        menuButton[0]->setStatus(Button::BUTTON_IN);
        menuButton[0]->loadButton(renderer, "PLAY");

        menuButton[1] = new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 441 - MENU_BUTTON_WIDTH / 2, 260);
        menuButton[1]->setStatus(Button::BUTTON_OUT);
        menuButton[1]->loadButton(renderer, "SOUND: ON");

        menuButton[2] = new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 441 - MENU_BUTTON_WIDTH / 2, 260 + 5 + MENU_BUTTON_HEIGHT);
        menuButton[2]->setStatus(Button::BUTTON_OUT);
        menuButton[2]->loadButton(renderer, "EXIT");

        currentButtonID = 0;
        currentMenuStatus = RUNNING;
    }
}

void Menu::render(SDL_Renderer* &renderer) {
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
    for (int i = 0; i < 3; ++i) menuButton[i]->renderButton(renderer);
}

void Menu::handleEvent(SDL_Event &e, SDL_Renderer* &renderer) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_DOWN:
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                currentButtonID = (currentButtonID + 1) % 3;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                break;
            case SDLK_UP:
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                currentButtonID = (currentButtonID + 2) % 3;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                break;
            case SDLK_s:
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                currentButtonID = (currentButtonID + 1) % 3;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                break;
            case SDLK_w:
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                currentButtonID = (currentButtonID + 2) % 3;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                break;
            case SDLK_RETURN:
                menuButton[currentButtonID]->setStatus(Button::BUTTON_PRESSED);
                switch (currentButtonID) {
                    case 0: currentMenuStatus = PLAY_BUTTON_PRESSED; break;
                    case 1:
                        menuButton[1]->changeSoundButton(renderer);
                        currentMenuStatus =  RUNNING; break;
                    case 2: currentMenuStatus = EXIT_BUTTON_PRESSED; break;
                }
                break;
        }
    }
}

int Menu::getStatus() const {
    return currentMenuStatus;
}
