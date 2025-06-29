#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Rock.h"
class Player;

class RockAttack : public AttackBehavior {
public:
	RockAttack(const std::string& name, PickableObject* obj);
	RockAttack(const std::string& name, PickableObject* obj, Player* player);

	virtual void attack()override;
private:
	PickableObject* m_rock = nullptr;
	Player* m_player = nullptr; 
	static bool m_register;

};