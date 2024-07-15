#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

Entity& player(manager.AddEntity());
Entity& wall(manager.AddEntity());

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
    map->LoadMap("assets/p16x16.map", 16, 16);

    player.AddComponent<TransformComponent>(0, 0, 32, 32, 2);
    player.AddComponent<SpriteComponent>("assets/player.png");
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");

    wall.AddComponent<TransformComponent>(300, 300, 320, 32, 1);
    wall.AddComponent<SpriteComponent>("assets/dirt.png");
    wall.AddComponent<ColliderComponent>("wall");
}

void Game::HandleEvents() {
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
}
void Game::Render() {
    SDL_RenderClear(renderer);
    //map->DrawMap();
    manager.Draw();
    SDL_RenderPresent(renderer);
}
void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y) {
    Entity& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(x, y, 32, 32, id);
}

