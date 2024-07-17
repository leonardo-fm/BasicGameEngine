#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 800, 640};

bool Game::isRunning = false;

Entity& player(manager.AddEntity());

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

    map = new Map("assets/terrain_ss.png", 2, 32);
    map->LoadMap("assets/map.map", 25, 20);

    player.AddComponent<TransformComponent>(400, 320, 32, 32, 2);
    player.AddComponent<SpriteComponent>("assets/player_animations.png", true);
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayer);
}

auto& tiles(manager.GetGroup(Game::groupMap));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& players(manager.GetGroup(Game::groupPlayer));

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
    SDL_Rect playerCollider = player.GetComponent<ColliderComponent>().collider;
    Vector2D playerPosition = player.GetComponent<TransformComponent>().position;
    
    manager.Refresh();
    manager.Update();

    for (Entity* collider : colliders) {
        SDL_Rect colliderRect = collider->GetComponent<ColliderComponent>().collider;
        if (Collision::AABB(colliderRect, playerCollider)) {
            player.GetComponent<TransformComponent>().position = playerPosition;
        }
    }
    
    camera.x = player.GetComponent<TransformComponent>().position.x - (camera.w / 2);
    camera.y = player.GetComponent<TransformComponent>().position.y - (camera.h / 2);

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > camera.w) camera.x = camera.w;
    if (camera.y > camera.h) camera.y = camera.h;
}

void Game::Render() {
    SDL_RenderClear(renderer);
    for (Entity* t : tiles) {
        t->Draw();
    }
    for (Entity* c : colliders) {
        c->Draw();
    }
    for (Entity* p : players) {
        p->Draw();
    }
    SDL_RenderPresent(renderer);
}
void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}

