//
// Created by Curry on 2026-01-14.
//

#include "GameObject.h"

#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y):
xPos(x), yPos(y), texture(TextureManager::load(path))
{}

GameObject::~GameObject() {
   if (texture) SDL_DestroyTexture(texture);
}

void GameObject::update(float deltaTime) {
   //Movement Logic here
   xPos += 60 * deltaTime;
   yPos += 60 * deltaTime;

   //Where do we want to crop the texture from?
   srcRect.x = srcRect.y = 0;
   //how much to crop
   srcRect.w = srcRect.h = 32;

   //Where to draw it?
  dstRect.x = static_cast<float>(xPos);
  dstRect.y = static_cast<float>(yPos);

    //Render Size
    dstRect.h = srcRect.h;
    dstRect.w = srcRect.w;
}

void GameObject::draw() {
    TextureManager::draw(texture, srcRect, dstRect);
}
