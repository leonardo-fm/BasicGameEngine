#ifndef Game_h
#define Game_h

#include "SDL.h"
#include <iostream>

class AssetManager;
class ColliderComponent;

class Game {
    
public:
    Game();
    ~Game();

    void Init(const char *title, int width, int height, bool fullscreen);
    void HandleEvents();
    bool Running() { return isRunning; }
    void Update();
    void Render();
    void Clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager *assetManager;

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayer,
        groupColliders,
        groupProjectiles
    };
private:
    SDL_Window *window;
};

#endif