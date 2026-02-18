//
// Created by Curry on 2026/02/17.
//

#ifndef PROJECT_ANIMATIONCLIP_H
#define PROJECT_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndicies;
};

#endif //PROJECT_ANIMATIONCLIP_H