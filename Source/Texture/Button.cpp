#include "Button.h"

Button::Button(int Width, int Height, int scrPosX, int scrPosY) {
    buttonRect = {scrPosX, scrPosY, Width, Height};
    normalText = new TextManager(28);
    selectText = new TextManager(28);
}

void Button::loadButton(SDL_Renderer* &renderer, std::string text) {
    if (text == "") return;
    normalText->loadRenderText(renderer, text, normalColor);
    selectText->loadRenderText(renderer, text, selectColor);
    bText = text;
}

void Button::renderButton(SDL_Renderer* &renderer) {
    if (buttonStatus == BUTTON_IN) {
        SDL_SetRenderDrawColor(renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        selectText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2);
    }
    else if (buttonStatus == BUTTON_OUT) {
        SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
        normalText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2);
    }
    SDL_RenderDrawRect(renderer, &buttonRect);
}

void Button::setStatus(const int status) {
    buttonStatus = status;
}

void Button::changeSoundButton(SDL_Renderer* &renderer) {
    if (bText == "SOUND: ON") bText = "SOUND: OFF";
    else bText = "SOUND: ON";
    normalText->loadRenderText(renderer, bText, normalColor);
    selectText->loadRenderText(renderer, bText, selectColor);
    buttonStatus = BUTTON_IN;
}
