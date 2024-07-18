#include "Game.h"

#include <sstream>

#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "AssetManager.h"
#include "SDL_ttf.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 800, 640};

AssetManager *Game::assetManager = new AssetManager(&manager);

bool Game::isRunning = false;

Entity& player(manager.AddEntity());
Entity& label(manager.AddEntity());

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

    if (TTF_Init() == -1) {
        std::cout << "Error Init SDL_TTF" << std::endl;
    }
    
    assetManager->AddTexture("terrain", "assets/terrain_ss.png");
    assetManager->AddTexture("player", "assets/player_animations.png");
    assetManager->AddTexture("projectile", "assets/projectile.png");
    
    assetManager->AddFont("cour", "assets/cour.ttf", 16);
    
    map = new Map("terrain", 2, 32);
    map->LoadMap("assets/map.map", 25, 20);

    player.AddComponent<TransformComponent>(400, 320, 32, 32, 2);
    player.AddComponent<SpriteComponent>("player", true);
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayer);

    SDL_Color black = { 255, 255, 255, 255 };
    label.AddComponent<UILabel>(10, 10, "Hello world", "cour", black);
    
    assetManager->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
}

auto& tiles(manager.GetGroup(Game::groupMap));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& players(manager.GetGroup(Game::groupPlayer));
auto& projectiles(manager.GetGroup(Game::groupProjectiles));

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

    std::stringstream ss;
    ss << "Player position: " << playerPosition;
    label.GetComponent<UILabel>().SetLabelText(ss.str(), "cour");
    
    manager.Refresh();
    manager.Update();

    for (Entity* collider : colliders) {
        SDL_Rect colliderRect = collider->GetComponent<ColliderComponent>().collider;
        if (Collision::AABB(colliderRect, playerCollider)) {
            player.GetComponent<TransformComponent>().position = playerPosition;
        }
    }

    for (Entity* projectile : projectiles) {
        if (Collision::AABB(player.GetComponent<ColliderComponent>().collider, projectile->GetComponent<ColliderComponent>().collider)) {
            projectile->Destroy();
        }
    }
    
    camera.x = static_cast<int>(player.GetComponent<TransformComponent>().position.x - camera.w / 2.0);
    camera.y = static_cast<int>(player.GetComponent<TransformComponent>().position.y - camera.h / 2.0);

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
    for (Entity* p : projectiles) {
        p->Draw();
    }

    label.Draw();
    SDL_RenderPresent(renderer);
}
void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}

