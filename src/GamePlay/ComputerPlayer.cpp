#include "GamePlay/ComputerPlayer.h"


//void ComputerPlayer::changeState(std::unique_ptr<ComputerPlayerState> newState) {
//    if (m_state)
//        m_state->exit(*this);
//
//    m_state = std::move(newState);
//
//    if (m_state)
//        m_state->enter(*this);
//}

// === Hit tracking methods ===

void ComputerPlayer::onHit() {
    m_wasHit = true;
}

void ComputerPlayer::onKnockedDown() {
    m_wasKnockedDown = true;
}

bool ComputerPlayer::wasHit() const {
    return m_wasHit;
}

bool ComputerPlayer::wasKnockedDown() const {
    return m_wasKnockedDown;
}

void ComputerPlayer::clearHitFlags() {
    m_wasHit = false;
    m_wasKnockedDown = false;
}
