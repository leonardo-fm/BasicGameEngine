#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId GetComponentTypeId() {
    static ComponentId lastId = 0;
    return lastId++;
}

template <typename T>
inline ComponentId GetComponentTypeId() noexcept {
    static ComponentId typeId = GetComponentTypeId();
    return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
    virtual ~Component() {};
    
    Entity* entity;

    virtual void Init() {};
    virtual void Update() {};
    virtual void Draw() {};
};

class Entity {
public:
    void Update() {
        for (auto& component : components) component->Update();
    }
    void Draw() {
        for (auto& component : components) component->Draw();
    }
    bool isActive() { return active; }
    void Destroy() { active = false; }

    template <typename T>
    bool HasComponent() const {
        return componentBitSet[GetComponentTypeId<T>()];
    }

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[GetComponentTypeId<T>()] = c;
        componentBitSet[GetComponentTypeId<T>()] = true;

        c->Init();
        return *c;
    }

    template <typename T>
    T& GetComponent() const {
        Component* ptr(componentArray[GetComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
};

class Manager {
public:
    void Update() {
        for (auto& entity: entities) entity->Update();
    }
    void Draw() {
        for (auto& entity: entities) entity->Draw();
    }

    void Refresh() {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity) {
                return !mEntity->isActive();
            }), std::end(entities));
    }

    Entity& AddEntity() {
        Entity *e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return  *e;
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
};