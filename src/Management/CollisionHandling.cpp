#include "Management/CollisionHandling.h"
#include "GamePlay/Player.h"
#include "Objects/Weapons/Rock.h"
#include "Objects/Weapons/Box.h"
#include "Objects/PickableObject.h"
#include "PlayableObjectStates/PlayerStates/CollideWithObjectState.h"
#include "PlayableObjectStates/PlayerStates/JumpingState.h"
#include "PlayableObjectStates/PlayerStates/AttackState.h"
#include "PlayableObjectStates/ComputerPlayerState/AttackingState.h"
#include "Gameplay/ComputerPlayer.h"
#include "EventCommands/StoneHitCommand.h"
#include "EventCommands/BoxHitCommand.h"
#include "EventCommands/HandsAttackCommand.h"



#include "GamePlay/Enemy.h"
#include "GamePlay/Ally.h"
#include "GamePlay/Bandit.h"


#include <iostream>
#include <typeindex>
#include <map>

using Key = std::tuple<std::type_index, std::type_index, std::type_index>;
using CollisionFunc = void(*)(Object&, std::shared_ptr<PickableObject>);
using HitMap = std::map<Key, CollisionFunc>;



using KeyOO = std::pair<std::type_index, std::type_index>;
using ObjectCollisionFunc = void(*)(Object&, Object&);
using objectVsObjectMap = std::map<KeyOO, ObjectCollisionFunc>;



// picking object generic func
template <typename T>
void playerPickableObject(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
    Player& player = static_cast<Player&>(playerObj);
    auto& object = pickableObj;
    if (player.isHoldingWeapon(object))
        return;
    
	if (typeid(*player.getState()) == typeid(JumpingState) || typeid(*player.getState()) == typeid(AttackState))
	{
		return;
	}
    
    player.setState(std::make_unique<CollideWithObject>(Input::NONE, object));
}

//
// wrapper to insert into map
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
        ally.handleCommand((pickableObj->getHitCommand()));
    }
    else if (pickableObj->isExploded())
    {
        ally.handleCommand((pickableObj->getHitCommand()));
    }
    
}

void enemyAttacked(Object& playerObj, std::shared_ptr<PickableObject> pickableObj) {
    auto& enemy = static_cast<Enemy&>(playerObj);
    if (pickableObj->thrown() )
    {
        pickableObj->collide();
        enemy.handleCommand((pickableObj->getHitCommand()->clone()));
    }
    else if (pickableObj->isExploded())
    {
        enemy.handleCommand((pickableObj->getHitCommand()));
    }

}

void playerAttacked(Object& playerObj, std::shared_ptr<PickableObject> pickableObj)
{
    auto& player = static_cast<Player&>(playerObj);
    if (pickableObj->thrown())
    {
		pickableObj->collide();
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
    map[{ typeid(Bandit), typeid(Box), typeid(Ally)}] = &enemyAttackingAlly;
    map[{ typeid(Bandit), typeid(Box), typeid(Player)}] = &enemyAttacked;
    map[{ typeid(Player), typeid(Box), typeid(Bandit)}] = &enemyAttacked;
    map[{ typeid(Ally), typeid(Box), typeid(Bandit)}] = &enemyAttacked;

    //Rock
    map[{ typeid(Bandit), typeid(Rock), typeid(Ally)}] = &enemyAttackingAlly;
    map[{ typeid(Bandit), typeid(Rock), typeid(Player)}] = &enemyAttacked;
    map[{ typeid(Player), typeid(Rock), typeid(Bandit)}] = &playerAttacked;
    map[{ typeid(Ally), typeid(Rock), typeid(Bandit)}] = &enemyAttacked;


    //Box
    map[{ typeid(Ally), typeid(Box), typeid(Ally)}] = &friendlyFire;
    map[{ typeid(Ally), typeid(Box), typeid(Player)}] = &friendlyFire;
    map[{ typeid(Player), typeid(Box), typeid(Ally)}] = &friendlyFire;
    map[{ typeid(Bandit), typeid(Box), typeid(Bandit)}] = &friendlyFire;
    map[{ typeid(Player), typeid(Box), typeid(Player)}] = &friendlyFire;

    //Rock
    map[{ typeid(Ally), typeid(Rock), typeid(Ally)}] = &friendlyFire;
    map[{ typeid(Ally), typeid(Rock), typeid(Player)}] = &friendlyFire;
    map[{ typeid(Player), typeid(Rock), typeid(Ally)}] = &friendlyFire;
    map[{ typeid(Bandit), typeid(Rock), typeid(Bandit)}] = &friendlyFire;
    map[{ typeid(Player), typeid(Rock), typeid(Player)}] = &friendlyFire;
    
    
    return map;
}

void processCollision(Object& obj1, std::shared_ptr<PickableObject> obj2)
{
	
    static HitMap map = initializeCollisionMap();
    Object* holder = obj2->getHolder();
    std::type_index holderType = holder ? typeid(*holder) : typeid(void);
    //std::cout << typeid(obj1).name() << " collided with " << typeid(*obj2).name() << " IN STATUS: " << obj2->getStatus() << " and holder was " << holderType.name() << std::endl;
	auto it = map.find({ typeid(obj1), typeid(*obj2), holderType });
    if (it != map.end())
    {
        it->second(obj1, obj2);
    }
}



void playerVsenemy(Object& playerObj, Object& enemyObj)
{
	Player& player = static_cast<Player&>(playerObj);
	Enemy& enemy = static_cast<Enemy&>(enemyObj);

    if (enemy.getHitCooldown() > 0.f)
        return; //
    auto playerDirX = player.getDirection();
	auto enemyDirX = enemy.getDirection();
	if (player.getPosition().x < enemy.getPosition().x) // if player is on the left side of the enemy
	    if (playerDirX  < 0) 
		    return;
	if (player.getPosition().x > enemy.getPosition().x) // if player is on the right side of the enemy
        if(playerDirX == 1)
			return;

	auto playerState = player.getState();

	if (typeid(*playerState) == typeid(AttackState))
	{
		enemy.handleCommand(std::make_unique<HandsAttackCommand>());
        enemy.setHitCooldown(0.5f);
	}    
}

void enemyVSPlayer(Object& enemyObj, Object& playerObj) {
    Player& player = static_cast<Player&>(playerObj);
    Enemy& enemy = static_cast<Enemy&>(enemyObj);

    if (player.getHitCooldown() > 0.f)
        return;

    if (enemy.getPosition().x < player.getPosition().x)
    {
        if (enemy.getDirection() < 0)
            return;
    }
    else if (enemy.getPosition().x < player.getPosition().x)
    {
        if (enemy.getDirection() > 0)
            return;
    }

    auto enemyState = enemy.getState();
    if (typeid(*enemyState) == typeid(AttackingState))
    {
        alignAttacker(enemyObj, playerObj);
        player.setHitCooldown(0.3f);
        player.handleCommand(std::make_unique<HandsAttackCommand>());
        
    }
}

void enemyVSAlly(Object& Obj1, Object& Obj2) {
	auto& attacker  = static_cast<ComputerPlayer&>(Obj1);
	auto& attacked = static_cast<ComputerPlayer&>(Obj2);

	if (attacked.getHitCooldown() > 0.f)
		return;
    if (attacker.getPosition().x < attacked.getPosition().x)
    {
        if (attacker.getDirection() < 0)
            return;
    }
    else if (attacker.getPosition().x < attacked.getPosition().x)
    {
        if (attacker.getDirection() > 0)
            return;
    }

	auto enemyState = attacker.getState();
	if (typeid(*enemyState) == typeid(AttackingState))
	{
        alignAttacker(attacker, attacked);
		    attacked.handleCommand(std::make_unique<HandsAttackCommand>());
            attacked.setHitCooldown(0.2f);

	}
}

//PlayableObjec vs PlayebleObject collision

objectVsObjectMap initializeOvsOmap(){

    objectVsObjectMap map;

    map[{typeid(Player), typeid(Bandit)}] = &playerVsenemy;
	map[{typeid(Bandit), typeid(Player)}] = &enemyVSPlayer;
    map[{typeid(Bandit), typeid(Ally)}] = &enemyVSAlly;
	map[{typeid(Ally), typeid(Bandit)}] = &enemyVSAlly;

    return map;
}

void processCollision(Object& object1, Object& object2)
{
	static objectVsObjectMap map = initializeOvsOmap();
	//std::cout << "Processing collision between " << typeid(object1).name() << " and " << typeid(object2).name() << std::endl;
	auto it = map.find({ typeid(object1), typeid(object2) });
	if (it != map.end())
	{
		it->second(object1, object2);
	}
	
}

void alignAttacker(Object& enemyObj, Object& playerObj)
{
    sf::Vector2f playerPos = enemyObj.getPosition();
    sf::Vector2f targetPos = playerObj.getPosition();

    float dx = playerPos.x - targetPos.x;
    float sign = (dx >= 0) ? LEFT : RIGHT;
    float alignedY = targetPos.y;

    enemyObj.setPosition({ playerPos.x, alignedY });
}