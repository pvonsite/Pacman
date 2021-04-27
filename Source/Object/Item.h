#pragma once

#ifndef _ITEM_H_
#define _ITEM_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Item {
    private:
        int tileX, tileY;
        bool dead = false;
        SDL_Texture* itemTexture = nullptr;
    public:
        Item(SDL_Renderer* &renderer, const std::string imgPath);

        ~Item();

        int getPosX() const;

        int getPosY() const;

        bool isDestroyed() const;

        void spawnAt(const int tileX, const int tileY);

        void destroyItem();

        void renderItem(SDL_Renderer* &renderer);
};

#endif // _ITEM_H_
