#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

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
    
private:
    bool isRunning = false;
    SDL_Window *window;
};

#endif