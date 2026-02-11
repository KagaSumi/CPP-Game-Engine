//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_ENTITY_H
#define PROJECT_ENTITY_H
#include <array>
#include <cstddef>
#include <bitset>

#include "ComponentType.h"

//Create CONST that is evaluated at compile time (constexpr)
// 32 Components fits perfectly in a 32-bit int
constexpr std::size_t MAX_COMPONENTS = 32;

//Bitset[0] = 1 // array but 0 or 1
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
//Bit operations are useful, because they are fast. Useful for checking frames

//fixed-size array, where each index is a component
//idx correspond with ComponentType ID
//Use a fix # of components so there is no dynamic allocation for array (efficient)
using ComponentArray = std::array<void*, MAX_COMPONENTS>;

class Entity {
    bool active = true;
    ComponentArray componentArray{};
    ComponentBitSet componentBitSet{};

public:
    bool isActive() { return active; }
    void destroy() { active = false; }

    //Templates need to me implemented in header
    //Example:
    //Entity.hasComponent<Position>() -> returns true or false
    template<typename T>
    bool hasComponent() { return componentBitSet[getComponentTypeID<T>()]; }

    //template that can recieve multiple args
    //entity.addComponent<Position>(4,5)
    //entity.addComponent<Health>(4)
    template <typename T, typename... mArgs>
    T& addComponent(mArgs&&...args){
        //implements perfect forwarding
        //everything is not treated as a lvalue
        // more efficient with moves and temporaries
        T* component(new T{std::forward<mArgs>(args)...});

        //add new component to array
        componentArray[getComponentTypeID<T>()] = component;
        //update bitset to true
        componentBitSet[getComponentTypeID<T>()] = true;

        return *component;
    }

    template<typename T>
    T& getComponent() {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T>
    void deactivate() { componentBitSet[getComponentTypeID<T>()] = false; }
};
#endif //PROJECT_ENTITY_H


