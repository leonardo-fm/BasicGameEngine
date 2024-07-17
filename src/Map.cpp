#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map() { }
Map::~Map() { }

void Map::LoadMap(std::string mapPath, int sizeX, int sizeY, int gridSize) {
    char tile;
    std::fstream mapFile;
    mapFile.open(mapPath);

    int srcX, srcY;
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            srcY = atoi(&tile) * gridSize;
            
            mapFile.get(tile);
            srcX = atoi(&tile) * gridSize;
            
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }    
    }
    
    mapFile.close();
}