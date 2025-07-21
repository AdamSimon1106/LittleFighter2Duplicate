#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include <SFML/System/Vector2.hpp>

RetreatingState::RetreatingState() = default;

void RetreatingState::enter(PlayableObject& player) {
    player.dropHeldObj();


    player.setAniName("running");
    m_safeZone = player.getSafeZone();

}

void RetreatingState::update(PlayableObject& player, float deltaTime) {
    m_elapsedTime += deltaTime;
    
    sf::Vector2f retreatDirection = m_safeZone - player.getPosition();
    float length = std::sqrt(retreatDirection.x * retreatDirection.x + retreatDirection.y * retreatDirection.y);
    if (length != 0) {
        retreatDirection /= length;
    }
    player.move(retreatDirection * player.getSpeed() * 2.f * deltaTime);

    if (m_elapsedTime >= m_retreatDuration || m_safeZone == player.getPosition()) {
        // Done retreating — return to idle (or other smart decision)
        player.setState(std::make_unique<IdleState>());
        return;
    }
}

void RetreatingState::exit(ComputerPlayer& player) {

}

void RetreatingState::onHandsAttack(PlayableObject& player) {

}

void RetreatingState::onStoneHit(PlayableObject& player) {
    player.setState(std::make_unique<KnockedDownState>());
}
void RetreatingState::onBoxHit(PlayableObject& player)
{
    player.setState(std::make_unique<KnockedDownState>());
}
void RetreatingState::onExplosion(PlayableObject& player) {

}