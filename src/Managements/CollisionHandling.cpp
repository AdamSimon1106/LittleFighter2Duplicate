#include "Management/CollisionHandling.h"

#include "GamePlay/Player.h"
#include "Objects/Weapons/Rock.h"
#include "PlayerStates/CollideWithObjectState.h"
#include <map>
#include <typeindex>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
namespace {

    // ? פונקציית התנגשות: שחקן דורך על סלע ומרים אותו
    void playerRock(Object& playerObj, Object& rockObj) {
        auto& player = static_cast<Player&>(playerObj);
        auto& rock = static_cast<Rock&>(rockObj);

        if (player.isHeldWaepomSameAsWaepon(&rock))
            return;
        player.setState(std::make_unique<CollideWithObject>(Input::NONE, &rock));

    }


    // סימטריה – Rock ? Player
    void rockPlayer(Object& rockObj, Object& playerObj) {
        playerRock(playerObj, rockObj);
    }

    // טיפוסים
    using HitFunctionPtr = void(*)(Object&, Object&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    // רישום ההתנגשויות
    HitMap initializeCollisionMap() {
        HitMap map;

        map[{typeid(Player), typeid(Rock)}] = &playerRock;
        map[{typeid(Rock), typeid(Player)}] = &rockPlayer;

        return map;
    }

    // חיפוש פונקציית ההתנגשות המתאימה
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2) {
        static HitMap collisionMap = initializeCollisionMap();

        auto it = collisionMap.find({ class1, class2 });
        if (it != collisionMap.end())
            return it->second;

        return nullptr;
    }

} // end anonymous namespace

// הפונקציה הציבורית שמפעילה את ההתנגשות
void processCollision(Object& object1, Object& object2) {
    auto func = lookup(typeid(object1), typeid(object2));
    if (!func)
        throw UnknownCollision(object1, object2);

    func(object1, object2);
}
