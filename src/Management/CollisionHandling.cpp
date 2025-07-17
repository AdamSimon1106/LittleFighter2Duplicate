#include "Management/CollisionHandling.h"
#include "GamePlay/Player.h"
#include "Objects/Weapons/Rock.h"
#include "Objects/Weapons/Box.h"
#include "Objects/PickableObject.h"
#include "PlayableObjectStates/PlayerStates/CollideWithObjectState.h"
#include "PlayableObjectStates/PlayerStates/JumpingState.h"
#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "Gameplay/ComputerPlayer.h"
#include "EventCommands/StoneHitCommand.h"
#include "EventCommands/BoxHitCommand.h"
#include "GamePlay/Enemy.h"
#include "GamePlay/Ally.h"
#include "GamePlay/Bandit.h"


#include <iostream>
#include <typeindex>
#include <map>

using Key = std::tuple<std::type_index, std::type_index, std::type_index>;
using CollisionFunc = void(*)(Object&, std::shared_ptr<PickableObject>);
using HitMap = std::map<Key, CollisionFunc>;

//
// פונקציה גנרית — template — לאיסוף חפץ
//
template <typename T>
void playerPickableObject(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
	std::cout << "in playerPickableObject\n";
    Player& player = static_cast<Player&>(playerObj);
    auto& object = pickableObj;
    if (player.isHoldingWeapon(object))
        return;
    if(object->thrown())
	{
        object->putBack();
        std::cout << "in playerPickableObject before handle command\n"; return;
        player.handleCommand(object->getHitCommand());
		std::cout << "object is thrown, cannot pick it up\n"; return;
	}
    //not so nice!!!!!
	if (typeid(*player.getState()) == typeid(JumpingState) || typeid(*player.getState()) == typeid(AttackState))
	{
		return;
	}
    
    player.setState(std::make_unique<CollideWithObject>(Input::NONE, object));
}

//
// wrapper בשביל להכניס למפה
//
template <typename T>
void playerPickableObjectWrapper(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
    playerPickableObject<T>(playerObj, pickableObj);
}

void enemyAttackingAlly(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
	auto& ally = static_cast<Ally&>(playerObj);
	if(pickableObj->thrown())
    {
        pickableObj->collide();
		std::cout << "in computerPlayerPickable before handle command\n";
        ally.handleCommand((pickableObj->getHitCommand()));
    }
    else if (pickableObj->isExploded())
    {
        ally.handleCommand((pickableObj->getHitCommand()));
    }
    
}

void enemyAttacked(Object& playerObj, std::shared_ptr<PickableObject> pickableObj) {
    std::cout << pickableObj->getStatus() << std::endl;
    auto& enemy = static_cast<Enemy&>(playerObj);
    if (pickableObj->thrown() )
    {
        pickableObj->collide();
        std::cout << "in computerPlayerPickable before handle command\n";
        enemy.handleCommand((pickableObj->getHitCommand()->clone()));
    }
    else if (pickableObj->isExploded())
    {
        enemy.handleCommand((pickableObj->getHitCommand()->clone()));
    }

}

void playerAttacked(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
    auto& player = static_cast<Player&>(playerObj);
    if (pickableObj->thrown())
    {
		pickableObj->collide();
        std::cout << "in computerPlayerPickable before handle command\n";
        player.handleCommand((pickableObj->getHitCommand()));
    }
    else if (pickableObj->isExploded())
    {
        player.handleCommand((pickableObj->getHitCommand()));
    }
}

void friendlyFire(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
}
//
// initializeCollisionMap
//
HitMap initializeCollisionMap()
{
    HitMap map;

    map[{typeid(Player), typeid(Rock), typeid(void)}] = &playerPickableObjectWrapper<Rock>;
    map[{typeid(Player), typeid(Box), typeid(void)}] = &playerPickableObjectWrapper<Box>;
    //Box
    //map[{ typeid(Ally), typeid(Box), typeid(Bandit)}] = &enemyAttackingAlly;
    map[{ typeid(Bandit), typeid(Box), typeid(Ally)}] = &enemyAttackingAlly;
    map[{ typeid(Bandit), typeid(Box), typeid(Player)}] = &enemyAttacked;
    map[{ typeid(Player), typeid(Box), typeid(Bandit)}] = &enemyAttacked;
    map[{ typeid(Ally), typeid(Box), typeid(Bandit)}] = &enemyAttacked;

    //Rock
    map[{ typeid(Bandit), typeid(Rock), typeid(Ally)}] = &enemyAttackingAlly;
    map[{ typeid(Bandit), typeid(Rock), typeid(Player)}] = &enemyAttacked;
    map[{ typeid(Player), typeid(Rock), typeid(Bandit)}] = &playerAttacked;
    map[{ typeid(Ally), typeid(Rock), typeid(Bandit)}] = &enemyAttacked;

    //map[{ typeid(Ally), typeid(Rock), typeid(Bandit)}] = &enemyAttackingAlly;
    //map[{ typeid(Player), typeid(Rock), typeid(Bandit)}] = &playerAttackingEnemy;
    //Box
    //map[{ typeid(Ally), typeid(Box), typeid(Ally)}] = &friendlyFire;
    //map[{ typeid(Ally), typeid(Box), typeid(Player)}] = &friendlyFire;
    //map[{ typeid(Player), typeid(Box), typeid(Ally)}] = &friendlyFire;
    //map[{ typeid(Bandit), typeid(Box), typeid(Bandit)}] = &friendlyFire;
    //map[{ typeid(Player), typeid(Box), typeid(Player)}] = &friendlyFire;
    ////Rock
    //map[{ typeid(Ally), typeid(Rock), typeid(Ally)}] = &friendlyFire;
    //map[{ typeid(Ally), typeid(Rock), typeid(Player)}] = &friendlyFire;
    //map[{ typeid(Player), typeid(Rock), typeid(Ally)}] = &friendlyFire;
    //map[{ typeid(Bandit), typeid(Rock), typeid(Bandit)}] = &friendlyFire;
    //map[{ typeid(Player), typeid(Rock), typeid(Player)}] = &friendlyFire;
    
    
    return map;
}

void processCollision(Object& obj1, std::shared_ptr<PickableObject> obj2)
{
	
    static HitMap map = initializeCollisionMap();
    Object* holder = obj2->getHolder();
    std::type_index holderType = holder ? typeid(*holder) : typeid(void);
    std::cout << typeid(obj1).name() << " collided with " << typeid(*obj2).name() << " and holder was " << holderType.name() << std::endl;
	auto it = map.find({ typeid(obj1), typeid(*obj2), holderType });
    if (it != map.end())
    {
        it->second(obj1, obj2);
    }
}
