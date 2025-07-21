#include "Attacks/BoxAttack.h"
#include "Factory/Factory.h"
#include "Objects/Weapons/Box.h"
#include "Gameplay/Player.h"

BoxAttack::BoxAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player)
	: m_player(player), m_box(obj)
{
}

void BoxAttack::attack()
{
	if (m_box)
	{
		dynamic_cast<Box*>(m_box.get())->throwMe(m_player->getDirection(), m_player->getPosition().y);
		m_box = nullptr;

	}
}

bool BoxAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("b",
	[](const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player) {
		return std::make_unique<BoxAttack>(name, obj, player);
	});

