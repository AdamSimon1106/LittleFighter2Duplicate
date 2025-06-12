#include "ComputerPlayerState/BlockingState.h"
#include "GamePlay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"

BlockingState::BlockingState() = default;

void BlockingState::enter(ComputerPlayer& player) {
    player.setAnimation("Block");
    m_elapsedTime = 0.0f;
    player.setBlocking(true); // TODO: write m_isBlocking field in Player

}

void BlockingState::update(ComputerPlayer& player, float deltaTime) {
    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_blockDuration) {
        player.setBlocking(false);
        player.changeState(std::make_unique<IdleState>());
    }
}

void BlockingState::exit(ComputerPlayer& player) {
    player.setBlocking(false); // Ensure cleanup even if exited early
}
