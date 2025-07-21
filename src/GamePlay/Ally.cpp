#include "Gameplay/Ally.h"
#include "Gameplay/Player.h"
#include "Management/AnimationManager.h"
#include <iostream>


Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    resetHP();
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "ally";

}

Ally::Ally(PlayerData p) : ComputerPlayer(p)
{
    setPosition(getRandomYPosition(50, Y_BOUND+20, Y_BOUND+BOUNDS_HEIGHT-20));
    m_prevPosition = getPosition();
    m_hp = p.m_hp;
    m_potentialHp = p.m_hp;
    m_speed = p.m_speed;
    m_name = p.m_name;
    m_icon = p.m_chracterIcon;
    changeState(std::make_unique<IdleState>());
}


void Ally::update(float dt) {

    ComputerPlayer::update(dt);  
    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    updateScale();
    updateAnimation(dt);
    apllySprite();

}

void Ally::handleCollision() {
}




//Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
//    : ComputerPlayer(pos, name)
//{
//    m_speed = speed;
//    // Starts with IdleState
//    changeState(std::make_unique<IdleState>());
//}

bool Ally::isAlive() const {
    return m_alive;
}

void Ally::resetHP() {
    m_hp = ALLY_HP;
    m_potentialHp = ALLY_HP;
}
