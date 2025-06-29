//#include "Management/CollisionHandling.h"
//
//#include "GamePlay/Player.h"
//#include "Objects/Weapons/Rock.h"
//#include "PlayerStates/CollideWithObjectState.h"
//#include <map>
//#include <typeindex>
//#include <iostream>
//#include <SFML/Window/Keyboard.hpp>
//#include <memory>
//namespace {
//
//    // ? פונקציית התנגשות: שחקן דורך על סלע ומרים אותו
//    void playerRock(Object& playerObj, Object& rockObj) {
//        auto& player = static_cast<Player&>(playerObj);
//        auto& rock = static_cast<Rock&>(rockObj);
//
//        if (player.isHeldWaepomSameAsWaepon(&rock))
//            return;
//        player.setState(std::make_unique<CollideWithObject>(Input::NONE, &rock));
//
//    }
//
//
//    // סימטריה – Rock ? Player
//    void rockPlayer(Object& rockObj, Object& playerObj) {
//        playerRock(playerObj, rockObj);
//    }
//
//
//    // טיפוסים
//    using HitFunctionPtr = void(*)(Object&, Object&);
//    using Key = std::pair<std::type_index, std::type_index>;
//    using HitMap = std::map<Key, HitFunctionPtr>;
//
//    // רישום ההתנגשויות
//    HitMap initializeCollisionMap() {
//        HitMap map;
//
//        map[{typeid(Player), typeid(Rock)}] = &playerRock;
//        map[{typeid(Rock), typeid(Player)}] = &rockPlayer;
//
//        return map;
//    }
//
//    // חיפוש פונקציית ההתנגשות המתאימה
//    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2) {
//        static HitMap collisionMap = initializeCollisionMap();
//
//        auto it = collisionMap.find({ class1, class2 });
//        if (it != collisionMap.end())
//            return it->second;
//
//        return nullptr;
//    }
//
//} // end anonymous namespace
//
//// הפונקציה הציבורית שמפעילה את ההתנגשות
//void processCollision(Object& object1, Object& object2) {
//    auto func = lookup(typeid(object1), typeid(object2));
//    if (!func)
//        throw UnknownCollision(object1, object2);
//
//    func(object1, object2);
//}


#include "Management/CollisionHandling.h"
#include "GamePlay/Player.h"
#include "Objects/Weapons/Rock.h"
#include "Objects/Weapons/Knife.h"
#include "Objects/PickableObject.h"
#include "PlayerStates/CollideWithObjectState.h"
#include "PlayerStates/JumpingState.h"
#include "PlayerStates/AttackState.h"

#include <iostream>
#include <typeindex>
#include <map>

using CollisionFunc = void(*)(Object&, Object&);
using HitMap = std::map<std::pair<std::type_index, std::type_index>, CollisionFunc>;

//
// פונקציה גנרית — template — לאיסוף חפץ
//
template <typename T>
void playerPickableObject(Object& playerObj, Object& pickableObj)
{
    auto& player = static_cast<Player&>(playerObj);
    auto& object = static_cast<T&>(pickableObj);
    //not so nice!!!!!
	if (typeid(*player.getState()) == typeid(JumpingState) || typeid(*player.getState()) == typeid(AttackState))
	{
		return;
	}
    if (player.isHoldingWaepon(&object))
        return;
    
    player.setState(std::make_unique<CollideWithObject>(Input::NONE, &object));
}

//
// wrapper בשביל להכניס למפה
//
template <typename T>
void playerPickableObjectWrapper(Object& playerObj, Object& pickableObj)
{
    playerPickableObject<T>(playerObj, pickableObj);
}

//
// initializeCollisionMap
//
HitMap initializeCollisionMap()
{
    HitMap map;

    map[{typeid(Player), typeid(Rock)}] = &playerPickableObjectWrapper<Rock>;
	map[{typeid(Player), typeid(Knife)}] = &playerPickableObjectWrapper<Knife>;

    // אפשר להוסיף עוד חפצים:
    // map[{typeid(Player), typeid(Potion)}] = &playerPickableObjectWrapper<Potion>;
    // map[{typeid(Player), typeid(Sword)}] = &playerPickableObjectWrapper<Sword>;

    // אפשר גם לשים את הסימטריה אם תרצה:
    map[{typeid(Rock), typeid(Player)}] = &playerPickableObjectWrapper<Rock>;

    return map;
}

void processCollision(Object& obj1, Object& obj2)
{
    static HitMap map = initializeCollisionMap();

    auto it = map.find({ typeid(obj1), typeid(obj2) });
    if (it != map.end())
    {
        it->second(obj1, obj2);
    }
}
