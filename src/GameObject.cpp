﻿#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texture, int x, int y) {
    objTexture = TextureManager::LoadTexture(texture);

    xPos = x;
    yPos = y;
}

GameObject::~GameObject() {
    
}

void GameObject::Update() {
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h  *2;
    destRect.w = srcRect.w  *2;
    destRect.x = xPos;
    destRect.y = yPos;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
