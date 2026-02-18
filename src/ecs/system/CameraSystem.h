//
// Created by Curry on 2026/02/17.
//

#ifndef PROJECT_CAMERASYSTEM_H
#define PROJECT_CAMERASYSTEM_H
#include <memory>
#include <vector>

#include "Components.h"
#include "Entity.h"

class CameraSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        //find player
        for (auto& e : entities) {
            if (e-> hasComponent<PlayerTag>()) {
                playerEntity = e.get();
                break;
            }
        }

        if (!playerEntity) {return;}//no player


        auto& playerTransform = playerEntity->getComponent<Transform>();

        for (auto& e : entities) {
            if (e->hasComponent<Camera>()) {
                auto& cam = e.get()->getComponent<Camera>();

                //This positions the camera so the player is at the center of its view
                cam.view.x = playerTransform.position.x - cam.view.w / 2;
                cam.view.y = playerTransform.position.y - cam.view.h / 2;

                //clap camera
                //The camera is positioning itself so that the player is centered, but the player could walk off the screen
                // so that is why we clamp the camera to stay within the window
                if (cam.view.x < 0) cam.view.x = 0;
                if (cam.view.y < 0) cam.view.y = 0;

                if (cam.view.x > cam.worldWidth - cam.view.w) cam.view.x = cam.worldWidth - cam.view.w;
                if (cam.view.y > cam.worldHeight - cam.view.h) cam.view.y = cam.worldHeight- cam.view.h;

            }
        }
    };

};



#endif //PROJECT_CAMERASYSTEM_H