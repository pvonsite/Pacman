#include "TextManager.h"

TextManager::TextManager(int fontSize) {
    font = TTF_OpenFont(FONT_NAME.c_str(), fontSize);
    textTexture = nullptr;
    textSurface = nullptr;
}

TextManager:: ~TextManager() {
    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    if (textSurface != nullptr) {
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
}


void TextManager::loadRenderText(SDL_Renderer* &renderer, std::string text, SDL_Color textColor) {
    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void TextManager::renderText(SDL_Renderer* &renderer, int scrPosX, int scrPosY) {
    dsRect = {scrPosX - textSurface->w / 2, scrPosY - textSurface->h / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
}
