#pragma once

#include <string>

class Map {
public:
    Map();
    ~Map();

    void LoadMap(std::string mapPath, int sizeX, int sizeY);
};
