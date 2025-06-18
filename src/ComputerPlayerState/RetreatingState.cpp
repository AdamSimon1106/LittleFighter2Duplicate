#include "ComputerPlayerState/RetreatingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"
#include <SFML/System/Vector2.hpp>

RetreatingState::RetreatingState() = default;

void RetreatingState::enter(ComputerPlayer& player) {
    player.setAnimation("Retreat");
    m_elapsedTime = 0.f;
}

void RetreatingState::update(ComputerPlayer& player, float deltaTime) {
    m_elapsedTime += deltaTime;

    // Move away from nearest visible threat (for now just move left/up)
    // You can enhance this to analyze real threats nearby
    sf::Vector2f retreatDirection(-1.f, -1.f);
    player.move(retreatDirection * player.getSpeed() * deltaTime);

    if (m_elapsedTime >= m_retreatDuration) {
        // Done retreating — return to idle (or other smart decision)
        player.changeState(std::make_unique<IdleState>());
    }
}

void RetreatingState::exit(ComputerPlayer& player) {
    // Cleanup if needed
}
