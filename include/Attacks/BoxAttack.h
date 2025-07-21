#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Box.h"


class Player;

class BoxAttack : public AttackBehavior {
public:
	BoxAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player);
	virtual void attack() override;
private:
	std::shared_ptr<PickableObject> m_box = nullptr;
	PlayableObject* m_player = nullptr;
	static bool m_register;

};
