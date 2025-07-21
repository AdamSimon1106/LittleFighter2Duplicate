#include "PlayableObjectStates/ComputerPlayerState/KnockedDownState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"

KnockedDownState::KnockedDownState() = default;

void KnockedDownState::enter(PlayableObject& player) {
    player.dropHeldObj();

    player.setAniName("knocked");
    
    m_elapsedTime = 0.0f;
    
}

void KnockedDownState::update(PlayableObject& player, float deltaTime) {

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_recoveryTime) {
        
        player.setState(std::make_unique<IdleState>());
    }
}

void KnockedDownState::exit(ComputerPlayer& player) {
    
}

void KnockedDownState::onHandsAttack(PlayableObject& player) {

}

void KnockedDownState::onStoneHit(PlayableObject& player) {

}
void KnockedDownState::onBoxHit(PlayableObject& player)
{
}
void KnockedDownState::onExplosion(PlayableObject& player) {

}