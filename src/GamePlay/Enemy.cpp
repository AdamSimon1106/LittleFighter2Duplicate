#include "GamePlay/Enemy.h"
#include "Management/AnimationManager.h"


Enemy::Enemy(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    resetHP();
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "enemy";

}



void Enemy::update(float dt)
{
    ComputerPlayer::update(dt); 

    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    updateScale();
    updateAnimation(dt);
    apllySprite();

}

void Enemy::handleCollision() {
}




bool Enemy::isAlive() const {
    return m_alive;
}

void Enemy::resetHP() {
    m_hp = ENEMY_HP;
    m_potentialHp = ENEMY_HP;
}

