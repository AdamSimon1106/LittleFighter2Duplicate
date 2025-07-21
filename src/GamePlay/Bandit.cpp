#include "Gameplay/Bandit.h"
#include "Factory/Factory.h"
#include "management/ResourceManager.h"

Bandit::Bandit(const sf::Vector2f pos)
    :Enemy(pos, "bandit_ani"), m_attackRange(HANDS_ATTACK_RANGE)
{
    m_speed = ENEMY_SPEED;

}

void Bandit::handleCollision()
{

}



bool Bandit::m_registered = Factory<Enemy>::registerIt("b", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Bandit>(pos);
    });

