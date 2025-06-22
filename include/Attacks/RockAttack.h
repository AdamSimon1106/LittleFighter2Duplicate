#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Rock.h"

class RockAttack : public AttackBehavior {
public:
	RockAttack(const std::string& name, PickableObject* obj);
	virtual void attack()override;
private:
	PickableObject* m_rock;
	static bool m_register;

};