#pragma once

#include "../src/Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    float speed = 3;
    
    TransformComponent() {
        SetPosition(0, 0);
    }
    TransformComponent(float x, float y) {
        SetPosition(x, y);
    }

    void Init() override {
        SetVelocity(0, 0);   
    }
    void Update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
    
private:
    void SetPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    void SetVelocity(float x, float y) {
        velocity.x = x;
        velocity.y = y;
    }
};

