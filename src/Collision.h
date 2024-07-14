#pragma once
#include <SDL_rect.h>

class Collision {
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
};
