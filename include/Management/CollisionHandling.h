#pragma once

#include "Objects/Object.h" 
#include <stdexcept>
#include <typeinfo>

struct UnknownCollision : public std::runtime_error {
    UnknownCollision(Object& a, Object& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name()) {}
};

// General collision handling
void processCollision(Object& object1, std::shared_ptr<PickableObject> object2);
void processCollision(Object& object1, Object& object2);
void alignAttacker(Object& enemyObj, Object& playerObj);

