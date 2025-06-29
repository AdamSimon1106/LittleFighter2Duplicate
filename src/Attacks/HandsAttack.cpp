#include "Attacks/HandsAttack.h"
#include "Factory/Factory.h"

HandsAttack::HandsAttack()
{
}

void HandsAttack::attack()
{
	std::cout << "in HandsAttack\n";
}

bool HandsAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("h",
	[](const std::string& name, PickableObject* obj, Player* player) {
		return std::make_unique<HandsAttack>();
	});
