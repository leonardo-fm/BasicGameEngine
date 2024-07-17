#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    
    TransformComponent *transform;

    ColliderComponent(const std::string tag) {
        this->tag = tag;
    }
    ColliderComponent(const std::string tag, int xPos, int yPos, int size) {
        this->tag = tag;
        collider.x = xPos;
        collider.y = yPos;
        collider.h = collider.w = size;
    }
    
    void Init() override {
        if (!entity->HasComponent<TransformComponent>()) {
            entity->AddComponent<TransformComponent>();
        }
        transform = &entity->GetComponent<TransformComponent>();

        texture = TextureManager::LoadTexture("assets/collider.png");
        srcRect = { 0, 0, 32, 32 };
        destRect = { collider.x, collider.y, collider.w, collider.h };
    }
    void Update() override {
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.h = transform->height * transform->scale;
            collider.w = transform->width * transform->scale;
        }

        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
    }
    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};