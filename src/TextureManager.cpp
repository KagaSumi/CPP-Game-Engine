//
// Created by Curry on 2026-01-14.
//

#include "TextureManager.h"
#include <iostream>
#include <ostream>
#include <Game.h>

//Doesn't create any extra mem, find reference of object
extern Game *game;
std::unordered_map<std::string, SDL_Texture *> TextureManager::textures;

//load our texture with a path
SDL_Texture *TextureManager::load(const char *path) {
    //Caching
    //Check if texture alr exists in the map
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }
    //A surface represent an image in ram
    SDL_Surface *tempSurface = IMG_Load(path);
    //Do we want to do any pre-process before offloading to GPU?

    if (!tempSurface) {
        std::cout << "Failed to load image: " << path << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    SDL_DestroySurface(tempSurface);

    //Check if creation is successful
    if (!texture) {
        std::cout << "Failed to create texture from: " << path << std::endl;
        return nullptr;
    }
    //store new texture in cache
    textures[path] = texture;

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst) {
    //draw texture to screen from vram
    SDL_RenderTexture(game->renderer, texture, &src, &dst);
}

void TextureManager::clean() {
    for (auto& tex: textures) {
        SDL_DestroyTexture(tex.second);
        tex.second = nullptr;
    }
    textures.clear();
}