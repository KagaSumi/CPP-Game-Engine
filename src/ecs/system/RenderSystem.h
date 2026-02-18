//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_RENDERSYSTEM_H
#define PROJECT_RENDERSYSTEM_H
#include <memory>
#include <vector>

#include <Entity.h>
#include "Components.h"
#include "TextureManager.h"

class RenderSystem {
    public:
    void render(std::vector<std::unique_ptr<Entity>> & entities) {
        for (auto& entity: entities) {
            if (entity-> hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();
                sprite.dst.x = t.position.x;
                sprite.dst.y = t.position.y;
                TextureManager::draw(sprite.Texture,sprite.src,sprite.dst);


                //if entity has animation, update souce rect
                if (entity->hasComponent<Animation>()) {
                    auto anim = entity->getComponent<Animation>();
                    sprite.src = anim.clips[anim.currentClip].frameIndicies[anim.currentFrame];
                }
            }
        }
    }
};
#endif //PROJECT_RENDERSYSTEM_H