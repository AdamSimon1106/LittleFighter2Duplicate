#include "ComputerPlayerState/KnockedDownState.h"
#include "GamePlay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"

KnockedDownState::KnockedDownState() = default;

void KnockedDownState::enter(ComputerPlayer& player) {
    player.setAnimation("KnockDown");
    m_elapsedTime = 0.0f;
    player.setControllable(false); // TODO: write m_controllabe field in Player
}

void KnockedDownState::update(ComputerPlayer& player, float deltaTime) {
    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_recoveryTime) {
        player.setControllable(true);
        player.changeState(std::make_unique<IdleState>());
    }
}

void KnockedDownState::exit(ComputerPlayer& player) {
    player.setControllable(true); // Restore control in any case
}
