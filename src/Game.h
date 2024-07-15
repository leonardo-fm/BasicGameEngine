#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

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

    static void AddTile(int id, int x, int y);

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
private:
    bool isRunning = false;
    SDL_Window *window;
};

#endif