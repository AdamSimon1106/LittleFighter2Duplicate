#include "Gameplay/Ally.h"

Ally::Ally(const std::string& name, float speed)
    : ComputerPlayer(name), m_speed(speed)
{

    // Start with IdleState
    changeState(std::make_unique<IdleState>());
}

bool Ally::isAlive() const {
    return m_alive;
}
