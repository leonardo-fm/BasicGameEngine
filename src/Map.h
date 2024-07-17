#pragma once

#include <string>

class Map {
public:
    Map(const char *filePath, int scale, int tileSize);
    ~Map();

    void LoadMap(std::string mapPath, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xPos, int yPos);
    
private:
    const char *mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};
