#pragma once
#include "Attacks/AttackBehavior.h"

class HandsAttack : public AttackBehavior{
public:
	HandsAttack();
	virtual void attack() override;
private:
	static bool m_register;
};
