#include "Item.h"

Item::Item(SDL_Renderer* &renderer, const std::string imgPath) {
    tileX = 0; tileY = 0;
    dead = true;
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    itemTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
}


Item::~Item() {
    SDL_DestroyTexture(itemTexture);
    itemTexture = nullptr;
}

int Item::getPosX() const {
    return tileX;
}

int Item::getPosY() const {
    return tileY;
}

bool Item::isDestroyed() const {
    return dead;
}

void Item::spawnAt(const int tileX, const int tileY) {
    this->tileX = tileX;
    this->tileY = tileY;
    dead = false;
}

void Item::destroyItem() {
    dead = true;
}

void Item::renderItem(SDL_Renderer* &renderer) {
    SDL_Rect dsRect = {tileX * 16 + 210, tileY * 16 - 7, 30, 30};
    SDL_RenderCopy(renderer, itemTexture, nullptr, &dsRect);
}
