#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId GetNewComponentTypeId() {
    static ComponentId lastId = 0u;
    return lastId++;
}

template <typename T>
inline ComponentId GetComponentTypeId() noexcept {
    static ComponentId typeId = GetNewComponentTypeId();
    return typeId;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

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
    Entity(Manager& mManager) : manager(mManager) { }
    void Update() {
        for (auto& component : components) component->Update();
    }
    void Draw() {
        for (auto& component : components) component->Draw();
    }
    bool IsActive() { return active; }
    void Destroy() { active = false; }

    bool HasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }
    void AddGroup(Group mGroup);
    void RemoveGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }
    
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
    Manager& manager;
    
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
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
        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupedEntetied[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v),
                [i](Entity *mEntity) {
                return !mEntity->IsActive() || !mEntity->HasGroup(i);
            }), std::end(v)); 
        }
        
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity) {
                return !mEntity->IsActive();
            }), std::end(entities));
    }

    void AddToGroup(Entity *mEntity, Group mGroup) {
        groupedEntetied[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& GetGroup(Group mGroup) {
        return  groupedEntetied[mGroup];
    }
    
    Entity& AddEntity() {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return  *e;
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntetied;
};