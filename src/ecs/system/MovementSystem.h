//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_MOVEMENTSYSTEM_H
#define PROJECT_MOVEMENTSYSTEM_H
#include <memory>
#include <vector>

#include <Entity.h>
#include "Components.h"

class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>> & entities, float dt) {
        for (auto& entity: entities) {
            if (entity -> hasComponent<Transform>() && entity -> hasComponent<Velocity>()) {
                auto& t = entity->getComponent<Transform>();
                auto& v = entity->getComponent<Velocity>();
                //t.position.x += 60 * dt;
                //t.position.y += 60 * dt;

                //track previous frame position
                t.oldPosition = t.position;

                Vector2D directionVec = v.direction;
                //normalizing
                directionVec.normalize();

                //Vector 2d needs an operation function to multiply a float to itself
                Vector2D velocityVectory = v.speed * directionVec;

                t.position += velocityVectory * dt;
            }
        }
    }
};
#endif //PROJECT_MOVEMENTSYSTEM_H