#pragma once

#include "../src/Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;
    TransformComponent() {
        SetPosition(0, 0);
    }
    TransformComponent(float x, float y) {
        SetPosition(x, y);
    }

    void Update() override { }
    
private:
    void SetPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
};

