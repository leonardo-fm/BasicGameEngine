#pragma once

#include <string>

class Map {
public:
    Map(std::string texId, int scale, int tileSize);
    ~Map();

    void LoadMap(std::string mapPath, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xPos, int yPos);
    
private:
    std::string textureId;
    int mapScale;
    int tileSize;
    int scaledSize;
};
