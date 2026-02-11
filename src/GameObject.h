//
// Created by Curry on 2026-01-14.
//

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

#include "Game.h"

class GameObject {
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update(float deltaTime);
    void draw();

private:
    float xPos{}, yPos{};
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
};

#endif //PROJECT_GAMEOBJECT_H