#include "GamePlay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"
#include "PlayableObjectStates/ComputerPlayerState/ApproachingEnemyState.h"
#include "PlayableObjectStates/ComputerPlayerState/DeadState.h"
#include "Gameplay/Player.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(const sf::Vector2f pos, const std::string& name) : PlayableObject(pos, name)
{
    m_state = std::make_unique<IdleState>();
    m_state->enter(*this);
}
ComputerPlayer::ComputerPlayer(PlayerData p) : PlayableObject(p.m_animationSheet,p.m_chracterIcon)
{
    m_state = std::make_unique<IdleState>();
    m_state->enter(*this);
}
void ComputerPlayer::update(float dt)
{
    if (m_hitCooldown > 0.f)
        m_hitCooldown -= dt;

    if (m_attackTimer) {

        m_attackCoolDown += dt;

        if (m_attackCoolDown >= m_attackWaitingTime) {
            m_canAttack = true;
            m_attackTimer = false;
            m_attackCoolDown = 0.f;
        }
    }
    else {
        m_canAttack = true; 
    }

    Object::update(dt);
    m_prevPosition = getPosition();
    if (m_state) {

        m_state->update(*this, dt);
    }
    updateHp();
    updateDirection();

}
void ComputerPlayer::changeState(std::unique_ptr<ComputerPlayerState> newState) {

    m_state = std::move(newState);

    if (m_state)
        m_state->enter(*this);
}

// Returns current state
PlayableObjectState* ComputerPlayer::getState() const {
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


void ComputerPlayer::setTarget(std::shared_ptr<Object> obj) {
    m_target = obj;
}


std::shared_ptr<Object> ComputerPlayer::getTarget()
{
    return m_target;
}


void ComputerPlayer::setBlocking(bool blocking)
{
    m_blocking = blocking;
}

void ComputerPlayer::setControllable(bool control)
{
    m_controllable = control;
}

void ComputerPlayer::performAttack(PlayableObject& target)
{

}

void ComputerPlayer::pickUp(PickableObject& pickable)
{


}

void ComputerPlayer::updateDirection()
{
    m_dir = m_prevPosition.x < getPosition().x ? Direction::RIGHT : Direction::LEFT;
}

void ComputerPlayer::onStoneHit()
{
    moveSprite({ static_cast<float>(m_xdirHit) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onStoneHit(*this);
}

void ComputerPlayer::onBoxHit()
{
    moveSprite({ static_cast<float>(m_xdirHit) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onBoxHit(*this);
}

void ComputerPlayer::onHandsAttack()
{
    moveSprite({ static_cast<float>(m_xdirHit) * 10, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onHandsAttack(*this);
}

void ComputerPlayer::onExplosion()
{
    moveSprite({ static_cast<float>(m_direction.x) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<DeadState>());
    }
    m_state->onExplosion(*this);
}


