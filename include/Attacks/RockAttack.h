#pragma once
#include "Attacks/AttackBehavior.h"

class RockAttack : public AttackBehavior{
public:
	virtual void attack()override;
};
