#include "Attacks/KnifeAttack.h"
#include "Factory/Factory.h"
#include "Gameplay/Player.h"


KnifeAttack::KnifeAttack(const std::string& name, PickableObject* obj)
	: m_knife(obj)
{
	std::cout << " creating attack\n";
}

KnifeAttack::KnifeAttack(const std::string& name, PickableObject* obj, Player* player)
	:m_player(player), m_knife(obj)
{
	std::cout << " creating attack with player\n";
}

void KnifeAttack::attack()
{
	std::cout << "in KnifeAttack::attack\n";
	if (m_knife)
	{
		m_knife->playAttack();
		m_knife = nullptr;
	}
}


bool KnifeAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("k",
	[](const std::string& name, PickableObject* obj, Player* player) {
		return std::make_unique<KnifeAttack>(name, obj, player);
	});
