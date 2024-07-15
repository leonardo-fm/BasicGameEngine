#pragma once

#include "ECS.h"
#include  "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileId;
    const char *spritePath;
    
    TileComponent() = default;
    TileComponent(int x, int y, int h, int w, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.h = h;
        tileRect.w = w;

        tileId = id;

        switch (id) {
        case 0:
            spritePath = "assets/dirt.png";
            break;
        case 1:
            spritePath = "assets/grass.png";
            break;
        case 2:
            spritePath = "assets/water.png";
            break;
        default:
            break;
        }
    }

    void Init() override {
        entity->AddComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.h, tileRect.w, 1);
        transform = &entity->GetComponent<TransformComponent>();

        entity->AddComponent<SpriteComponent>(spritePath);
        sprite = &entity->GetComponent<SpriteComponent>();
    }
};
