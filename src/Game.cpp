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

const char* mapFile = "assets/terrain_ss.png";

enum groupLabels : std::size_t {
    groupMap,
    groupPlayer,
    groupEnemies,
    groupColliders
};

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
    map->LoadMap("assets/map.map", 25, 20, 32);

    player.AddComponent<TransformComponent>(0, 0, 32, 32, 2);
    player.AddComponent<SpriteComponent>("assets/player_animations.png", true);
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayer);
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

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayer));
auto& enemies(manager.GetGroup(groupEnemies));

void Game::Render() {
    SDL_RenderClear(renderer);
    for (Entity* t : tiles) {
        t->Draw();
    }
    for (Entity* p : players) {
        p->Draw();
    }
    for (Entity* e : enemies) {
        e->Draw();
    }
    SDL_RenderPresent(renderer);
}
void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos) {
    Entity& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(srcX, srcY, xPos, yPos, mapFile);
    tile.AddGroup(groupMap);
}

