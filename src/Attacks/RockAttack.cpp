#include "Attacks/RockAttack.h"
#include "Factory/Factory.h"
#include "Objects/Weapons/Rock.h"
#include "Gameplay/Player.h"



RockAttack::RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj)
    :m_rock(obj)
{
}

RockAttack::RockAttack(const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player)
	:m_player(player), m_rock(obj)
{

}

void RockAttack::attack()
{
    if (m_rock)
    {

		dynamic_cast<Rock*>(m_rock.get())->throwMe(m_player->getDirection(), m_player->getPosition().y);
		m_rock = nullptr; 
    } 
}



bool RockAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("r",
    [](const std::string& name, std::shared_ptr<PickableObject> obj, PlayableObject* player) {
        return std::make_unique<RockAttack>(name, obj, player);
    });




