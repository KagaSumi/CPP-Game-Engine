//
// Created by Curry on 2026-02-04.
//
#include "World.h"

#include <iostream>

World::World() {
    //subscribe to collision event
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision){
        if (collision.entityA == nullptr || collision.entityB == nullptr) return;
        if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;


        if  (colliderA.tag == "player" && colliderB.tag == "item") {
            player = collision.entityA;
            item = collision.entityB;
        } else if (colliderA.tag == "item" && colliderB.tag == "player") {
            player = collision.entityB;
            item = collision.entityA;
        }

        if (player && item) {
            item->destroy();
        }

        //player vs wall.
        if  (colliderA.tag == "player" && colliderB.tag == "wall") {
            player = collision.entityA;
            wall = collision.entityB;
        } else if (colliderA.tag == "wall" && colliderB.tag == "player") {
            player = collision.entityB;
            wall = collision.entityA;
        }
        if (player && wall) {
            //stop player
            auto& t = player->getComponent<Transform>();
            t.position = t.oldPosition;
        }
    });

    //eventManager.subscribe<CollisionEvent>(printCollision);
}

void printCollision(const CollisionEvent& collision) {
    if (collision.entityA == nullptr || collision.entityB == nullptr) return;
    std::cout <<"A collision occurred between entity " << collision.entityA->getComponent<Collider>().tag << " and " << collision.entityB->getComponent<Collider>().tag << std::endl;
}

