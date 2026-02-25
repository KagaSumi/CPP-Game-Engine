//
// Created by Curry on 2026-02-25.
//

#ifndef PROJECT_SPAWNTIMERSYSTEM_H
#define PROJECT_SPAWNTIMERSYSTEM_H
#include <memory>
#include <vector>

#include "Components.h"
#include "Entity.h"

class SpawnTimerSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const float dt) {
        for (auto& entity : entities) {
           if (entity->hasComponent<TimedSpawner>()) {
               auto& spawner = entity->getComponent<TimedSpawner>();
               spawner.timer -= dt;

               if (spawner.timer <= 0) {
                   spawner.timer = spawner.spawnInterval; // eg 2sec
                   spawner.spawnCallback(); //Create entity inside here

               }
           }
        }

    }
};
#endif //PROJECT_SPAWNTIMERSYSTEM_H