#pragma once

#include <map>
#include "SDL_ttf.h"
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager {
public:
    AssetManager(Manager *man);
    ~AssetManager();

    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string textureId);
    
    void AddTexture(std::string id, const char *path);
    SDL_Texture* GetTexture(std::string id);

    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);
    
private:
    Manager *manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};