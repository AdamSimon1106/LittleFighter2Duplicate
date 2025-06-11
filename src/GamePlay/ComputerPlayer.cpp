#include "GamePlay/ComputerPlayer.h"


void ComputerPlayer::changeState(std::unique_ptr<ComputerPlayerState> newState) {
    if (m_state)
        m_state->exit(*this);

    m_state = std::move(newState);

    if (m_state)
        m_state->enter(*this);
}