#include "Gameplay/Ally.h"

Ally::Ally(const sf::Vector2f pos, const std::string& name, float speed)
    : ComputerPlayer(pos, name)
{
    m_speed = speed;
    // Starts with IdleState
    changeState(std::make_unique<IdleState>());
}

bool Ally::isAlive() const {
    return m_alive;
}
