#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include <map>
#include "Animation.h"

class SpriteComponent : public Component {
public:
    int animationIndex = 0;
    std::map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    
    SpriteComponent() = default;
    SpriteComponent(const char *path) {
        SetTexture(path);
    }
    SpriteComponent(const char *path, bool isAnimated) {
        animated = isAnimated;
        Animation idle = Animation(0, 4, 250);
        Animation walk = Animation(1, 4, 250);
        animations.emplace("idle", idle);
        animations.emplace("walk", walk);

        Play("idle");
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
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
        srcRect.y = animationIndex * srcRect.h;
        
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale; 
        destRect.h = transform->height * transform->scale;     
    }
    void Draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void Play(const char *animationName) {
        frames = animations[animationName].frames;
        animationIndex = animations[animationName].index;
        speed = animations[animationName].speed;
    }
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;
};
