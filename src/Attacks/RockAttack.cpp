#include "Attacks/RockAttack.h"
#include "Factory/Factory.h"



RockAttack::RockAttack(const std::string& name, PickableObject* obj)
    :m_rock(obj)
{
    std::cout << " creating attack\n";
}

void RockAttack::attack()
{
    std::cout << "in RockAttack\n";
    if (m_rock)
    {
        m_rock->playAttack();
		m_rock = nullptr; 

    } 
}

bool RockAttack::m_register = Factory<AttackBehavior>::registerAttackBehavior("r",
    [](const std::string& name, PickableObject* obj) {
        return std::make_unique<RockAttack>(name, obj);
    });


