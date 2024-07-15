#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent *transform;

    ColliderComponent(const std::string tag) {
        this->tag = tag;
    }
    
    void Init() override {
        if (!entity->HasComponent<TransformComponent>()) {
            entity->AddComponent<TransformComponent>();
        }
        transform = &entity->GetComponent<TransformComponent>();
        Game::colliders.push_back(this);
    }
    void Update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.h = transform->height * transform->scale;
        collider.w = transform->width * transform->scale;
    }
};