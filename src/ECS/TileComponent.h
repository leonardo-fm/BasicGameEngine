#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    
    TileComponent() = default;
    TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path) {
        texture = TextureManager::LoadTexture(path);
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;

        destRect.x = xPos;
        destRect.y = yPos;
        destRect.w = destRect.h = 64;
    }
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
