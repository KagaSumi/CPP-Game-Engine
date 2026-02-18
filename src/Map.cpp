//
// Created by Curry on 2026-01-14.
//
#include "Map.h"

#include <cmath>

#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>

void Map::load(const char *path, SDL_Texture *ts) {
    tileset = ts;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    //Parse width and height of map
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    //parse terraindata
    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");
    std::string csv = data->GetText();
    std::stringstream ss(csv);
    tileData = std::vector(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;
            //read characters from a ss into val until hits comma or end of string
            if (!std::getline(ss, val, ',')) {break;}
            tileData[i][j] = std::stoi(val); //stoi is a string to integer converter
        }
    }

    //parse collider data
    auto* ObjectGroup = layer->NextSiblingElement("objectgroup");
    //create a for loop with initialization, condition and an increment
    for (auto* obj = ObjectGroup->FirstChildElement("object");
        obj != nullptr;
        obj = obj->NextSiblingElement("object")) {

        Collider c;
        c.rect.x = obj->FloatAttribute("x");
        c.rect.y = obj->FloatAttribute("y");
        c.rect.h = obj->FloatAttribute("height");
        c.rect.w = obj->FloatAttribute("width");
        colliders.push_back(c);
    }

    //parse coin data
    auto* CoinGroup = ObjectGroup->NextSiblingElement("objectgroup");
    for (auto* obj = CoinGroup->FirstChildElement("object");
        obj != nullptr;
        obj = obj->NextSiblingElement("object")) {
        Collider c;
        c.rect.x = obj->FloatAttribute("x");
        c.rect.y = obj->FloatAttribute("y");
        coins.push_back(c);
        }
}

void Map::draw(const Camera &cam) {
    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32;

    for (int row =0; row<height; row++) {
        for (int col =0; col<width; col++) {
            int type = tileData[row][col];


            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;

            //Move map relative to the Camera
            //Convert from world space to screen space
            dest.x = std::round(worldX - cam.view.x);
            dest.y = std::round(worldY - cam.view.y);

            switch (type) {
                case 1:
                    //Dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    //Grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    //Water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    break;
            }
            TextureManager::draw(tileset,src,dest);
        }
    }
}