//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_COMPONENTS_H
#define PROJECT_COMPONENTS_H
#include <functional>
#include <SDL3/SDL_render.h>

#include "Vector2D.h"
#include <string>
#include <unordered_map>

#include "AnimationClip.h"

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

struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{}; //time is accumulated for the current frame
    int currentFrame{}; //index of current frame in the clip
    float speed = 0.1f; //Time per frame
};

struct Camera {
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback{};
    float timer{};
};

//Game State, scene because might have multiple scenes
struct SceneState {
    int coinsCollected = 0;
};

struct PlayerTag{};
struct ProjectileTag{};

#endif //PROJECT_COMPONENTS_H