#include "Gameplay/Bandit.h"
#include "Factory/Factory.h"
#include "management/ResourceManager.h"

Bandit::Bandit()
    :Enemy(ResourceManager::instance().getTexture("bandit")), m_speed(2.5f), m_attackRange(60.f)
{
    

}

void Bandit::handleCollision()
{
}

void Bandit::update(const sf::Vector2f playarPos)
{
    move(playarPos);
}

void Bandit::move(const sf::Vector2f playerPos)
{   
    auto pos = m_sprite.getPosition();
    m_direction = playerPos - pos;

    float distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

    

    if (distance > m_attackRange) {
        sf::Vector2f normDir = m_direction / distance;

        m_sprite.move(normDir * m_speed);


        /*pos += normDir * m_speed;
        m_sprite.setPosition(pos);*/
    }
}

bool Bandit::m_registered = Factory<Enemy>::registerIt("b", []() {
    return std::make_unique<Bandit>();
    });

