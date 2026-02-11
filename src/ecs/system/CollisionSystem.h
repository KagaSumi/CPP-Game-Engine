//
// Created by Curry on 2026-02-04.
//

#ifndef PROJECT_COLLISIONSYSTEM_H
#define PROJECT_COLLISIONSYSTEM_H
#include <vector>
#include <memory>
#include "Entity.h"

//forward declaration
class World;

class CollisionSystem {
public:
    void update(World& world);
    private:
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);

};

#endif //PROJECT_COLLISIONSYSTEM_H