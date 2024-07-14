#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "../ECS/Components.h"

Map *map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
auto& player(manager.AddEntity());

Game::Game() {}
Game::~Game() {}

void Game::Init(const char *title, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystem Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window) std::cout << "Window created!" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    map = new Map();

    player.AddComponent<TransformComponent>();
    player.AddComponent<SpriteComponent>("assets/player.png");
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::Update() {
    manager.Refresh();
    manager.Update();

    player.GetComponent<TransformComponent>().position -= Vector2D(0, -5);
}

void Game::Render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.Draw();
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}

