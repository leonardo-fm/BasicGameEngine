#include "Game.h"

Game *game = nullptr;
int main(int argc, char *argv[]) {

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS; // milliseconds

    Uint32 framestart;
    int frameTime;
    
    game = new Game();
    game->Init("TestGame", 800, 640, false);
    
    while(game->Running()) {
        framestart = SDL_GetTicks();
        
        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - framestart;
        if (FRAME_DELAY > frameTime) SDL_Delay(FRAME_DELAY - frameTime);
    }

    game->Clean();
    return 0;
}