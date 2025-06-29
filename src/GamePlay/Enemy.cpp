#include "GamePlay/Enemy.h"
#include "Management/AnimationManager.h"


Enemy::Enemy(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "enemy";
}


void Enemy::update(float dt)
{
    ComputerPlayer::update(dt);  // זה מפעיל את ה־state
    if (m_currentAnimationName != m_aniName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName;
    }
    //std::cout << "my target is: " << m_target->getName() << std::endl;
    updateScale();
    updateAnimation(dt);
    apllySprite();
}

void Enemy::handleCollision() {
    // עדיין לא מוגדר מה קורה בהתנגשות, אז נשאיר ריק בינתיים
}




bool Enemy::isAlive() const {
    return m_alive;
}
