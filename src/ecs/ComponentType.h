//
// Created by Curry on 2026-01-21.
//

#ifndef PROJECT_COMPONENTTYPE_H
#define PROJECT_COMPONENTTYPE_H
#include <cstddef>

//Creating a type alias for std:size_t
//size_t is designed to represent sizes and indices because its unsigned its very large (long,long)
using ComponentTypeID = std::size_t;

//free function and defined in a header, each .cpp file that includes this .h
//Would get its own definition causing a linker error
//Using inline merges tem into 1 definition
//global counter generator, return uuid everything we call it making id static, means
// it will keep its value through multiple calls of this function

inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id = 0;
    return id++;
}

//Template allows generic types
//Can over load this function because these are different signatures

//getComponentTypeID<Position>() -> would always return 0
//GetComponentTypeID<Health>() -> would always return 1

template <typename T>
ComponentTypeID getComponentTypeID() {
    static  ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}


#endif //PROJECT_COMPONENTTYPE_H