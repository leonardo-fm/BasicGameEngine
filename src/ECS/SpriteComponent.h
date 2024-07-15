#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    SpriteComponent(const char *path) {
        SetTexture(path);
    }
    ~SpriteComponent() override {
        SDL_DestroyTexture(texture);
    }

    void SetTexture(const char *path) {
        texture = TextureManager::LoadTexture(path);
    }
    void Init() override {
        transform = &entity->GetComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }
    void Update() override {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale; 
        destRect.h = transform->height * transform->scale;     
    }
    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};
