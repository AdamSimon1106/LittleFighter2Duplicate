#include "Gameplay/Ally.h"
#include "Management/AnimationManager.h"
#include <iostream>


Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
    m_name = "ally";
}


void Ally::update(float dt) {
    ComputerPlayer::update(dt);  // זה מפעיל את ה־state
    if (m_currentAnimationName != m_aniName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName;
    }
    updateScale();
    updateAnimation(dt);
    apllySprite();
}

void Ally::handleCollision() {
    // עדיין לא מוגדר מה קורה בהתנגשות, אז נשאיר ריק בינתיים
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
