#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Knife.h"

class KnifeAttack : public AttackBehavior {
public:
	KnifeAttack(const std::string& name, PickableObject* obj);
	virtual void attack() override;
private:
	PickableObject* m_knife;
	static bool m_register;

};
