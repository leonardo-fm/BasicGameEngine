#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"

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

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayer,
        groupColliders
    };
private:
    SDL_Window *window;
};

#endif