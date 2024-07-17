#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/TileComponent.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(std::string texId, int scale, int tileSize) :
textureId(texId), mapScale(scale), tileSize(tileSize) {
    scaledSize = tileSize * scale;
}
Map::~Map() { }

void Map::LoadMap(std::string mapPath, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(mapPath);

    int srcX, srcY;
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            srcY = atoi(&tile) * tileSize;
            
            mapFile.get(tile);
            srcX = atoi(&tile) * tileSize;
            
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }    
    }

    mapFile.ignore();
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            if (tile == '1') {
                auto& tileCollider(manager.AddEntity());
                tileCollider.AddComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tileCollider.AddGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }    
    }
    
    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos) {
    Entity& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, textureId);
    tile.AddGroup(Game::groupMap);
}