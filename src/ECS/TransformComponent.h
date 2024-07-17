#pragma once

#include "../Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;
    
    float speed = 3;
    
    TransformComponent() {
        position.Zero();
    }
    TransformComponent(float x, float y) {
        SetPosition(x, y);
    }
    TransformComponent(float x, float y, int h, int w, int scale) {
        SetPosition(x, y);
        height = h;
        width = w;
        this->scale = scale;
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

