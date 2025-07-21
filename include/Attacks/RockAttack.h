#pragma once
#include "Attacks/AttackBehavior.h"
#include "Objects/Weapons/Rock.h"
class PlayableObject;

class RockAttack : public AttackBehavior {
public:
	RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj);
	RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player);

	virtual void attack()override;
private:
	std::shared_ptr<PickableObject> m_rock = nullptr;
	PlayableObject* m_player = nullptr;
	static bool m_register;

};