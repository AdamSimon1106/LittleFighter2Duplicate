#include "Attacks/HandsAttack.h"
#include "Factory/Factory.h"

HandsAttack::HandsAttack()
{
}

void HandsAttack::attack()
{
}

bool HandsAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("h",
	[](const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player) {
		return std::make_unique<HandsAttack>();
	});
