#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void Init() override {
        transform = &entity->GetComponent<TransformComponent>();
        sprite = &entity->GetComponent<SpriteComponent>();
    }

    void Update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                transform->velocity.y = -1;
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            default:
                break;
            }
            sprite->Play("walk");
        }
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                transform->velocity.y = 0;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break; 
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            default:
                break;
            }
            sprite->Play("idle");
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
    }
};