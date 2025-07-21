#include "PlayableObjectStates/ComputerPlayerState/GotHitState.h"
#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"

GotHitState::GotHitState() = default;

void GotHitState::enter(PlayableObject& player) {
    player.dropHeldObj();

    player.setAniName("gothit");
    m_elapsedTime = 0.0f;
}

void GotHitState::update(PlayableObject& player, float deltaTime) {

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_recoveryTime) {
        player.setState(std::make_unique<IdleState>());
    }
}

void GotHitState::exit(ComputerPlayer& player) {
}

void GotHitState::onHandsAttack(PlayableObject& player) {

}

void GotHitState::onStoneHit(PlayableObject& player) {

}
void GotHitState::onExplosion(PlayableObject& player) {

}