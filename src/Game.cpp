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

Entity& tile0(manager.AddEntity());
Entity& tile1(manager.AddEntity());
Entity& tile2(manager.AddEntity());

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

    tile1.AddComponent<TileComponent>(250, 250, 32, 32, 0);
    tile1.AddComponent<ColliderComponent>("dirt");
    tile2.AddComponent<TileComponent>(150, 150, 32, 32, 1);
    tile2.AddComponent<ColliderComponent>("grass");
    tile0.AddComponent<TileComponent>(200, 200, 32, 32, 2);

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

    for (ColliderComponent* cc : colliders) {
        Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
    }
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

