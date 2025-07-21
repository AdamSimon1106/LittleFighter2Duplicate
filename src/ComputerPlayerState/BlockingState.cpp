#include "PlayableObjectStates/ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/RetreatingState.h"


BlockingState::BlockingState() = default;

void BlockingState::enter(PlayableObject& player) {
    player.dropHeldObj();

    player.setAniName("blocking");
    m_elapsedTime = 0.0f;

}

void BlockingState::update(PlayableObject& player, float deltaTime) {

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_blockDuration) {
        player.setState(std::make_unique<RetreatingState>());
    }
}

void BlockingState::exit(ComputerPlayer& player) {
    player.setBlocking(false); 
}

void BlockingState::name() {
}
void BlockingState::onHandsAttack(PlayableObject& player) {
   
}

void BlockingState::onStoneHit(PlayableObject& player) {

}
void BlockingState::onBoxHit(PlayableObject& player)
{
}
void BlockingState::onExplosion(PlayableObject& player) {

}
