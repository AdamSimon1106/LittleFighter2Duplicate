#include "GamePlay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"
#include "ComputerPlayerState/ApproachingEnemyState.h"

void ComputerPlayer::update(float dt)
{
    if (m_state) {
        m_state->update(*this, dt);
    }
}
void ComputerPlayer::changeState(std::unique_ptr<ComputerPlayerState> newState) {
    if (m_state)
        m_state->exit(*this);

    m_state = std::move(newState);

    if (m_state)
        m_state->enter(*this);
}

// Returns current state
ComputerPlayerState* ComputerPlayer::getState() const {
    return m_state.get();
}

bool ComputerPlayer::needsEnemyTracking() const {
    if (!m_state) return false;

    return dynamic_cast<IdleState*>(m_state.get()) ||
        dynamic_cast<ApproachingEnemyState*>(m_state.get()); // return true only if IdleState or ApproachingEnemyState.
}



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

// Calculates the Euclidean distance between two points
float ComputerPlayer::distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

void ComputerPlayer::setTargetEnemy(PlayableObject* target) {
    m_target = target;
}

sf::Vector2f ComputerPlayer::getPosition()
{
    return m_position;
}