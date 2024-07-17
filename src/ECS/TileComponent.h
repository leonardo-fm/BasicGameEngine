#pragma once

#include "ECS.h"
#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"

class TileComponent : public Component {
public:
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    Vector2D position;
    
    TileComponent() = default;
    TileComponent(int srcX, int srcY, int xPos, int yPos, int size, int scale, const char* path) {
        texture = TextureManager::LoadTexture(path);
        
        position.x = xPos;
        position.y = yPos;
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = size;

        destRect.x = xPos;
        destRect.y = yPos;
        destRect.w = destRect.h = size * scale;
    }
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    void Update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }
    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
