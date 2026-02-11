//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_COMPONENTS_H
#define PROJECT_COMPONENTS_H
#include <SDL3/SDL_render.h>

#include "Vector2D.h"
#include <string>

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};

};

//direction and speed
struct Velocity {
    Vector2D direction{};
    float speed{};
};

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct Sprite {
    SDL_Texture* Texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
};

#endif //PROJECT_COMPONENTS_H