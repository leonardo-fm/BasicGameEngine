#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface *tmpSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect) {
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
