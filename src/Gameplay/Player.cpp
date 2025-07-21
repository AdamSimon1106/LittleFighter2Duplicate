#include "Gameplay/Player.h"
#include <algorithm>           
#include "PlayableObjectStates/PlayerStates/StandingState.h"
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"
#include "PlayableObjectStates/ComputerPlayerState/DeadState.h"
#include "PlayableObjectStates/PlayerStates/PlayerDeadState.h"
#include "Management/AnimationManager.h"

Player::Player(const sf::Vector2f pos, const std::string& name, float speed)
    : PlayableObject(pos, name)
{
    resetHP();
	m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
    m_speed = speed;
    m_name = "player";
    this->setState(std::make_unique<StandingState>(RELEASE_RIGHT));
    m_state->enter(*this);

}

Player::Player(PlayerData data) : PlayableObject(data.m_animationSheet,data.m_chracterIcon)
{
    setPosition(getRandomYPosition(50, Y_BOUND + 20.f, Y_BOUND + BOUNDS_HEIGHT - 20.f));
    m_prevPosition = getPosition();
    m_hp = data.m_hp;
    m_potentialHp = data.m_hp;
    m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
    m_speed = data.m_speed;
    m_name = data.m_name;
    m_icon = data.m_chracterIcon;
    this -> setState(std::make_unique<StandingState>(RELEASE_RIGHT));
    m_state->enter(*this);
}

// Updates m_direction according to arrow keys
void Player::handleInput(sf::Event event)
{

    Input input = getEventType(event);

    auto state = m_state->handleInput(input);

    if (state)
    {
        m_state = std::move(state);
        m_state->enter(*this);
    }
}

void Player::update(float dt)
{
    if (m_hitCooldown > 0.f)
        m_hitCooldown -= dt;

    Object::update(dt);
    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    move(dt);
    m_state->update(*this, dt);
    updateAnimation(dt);
    apllySprite();
    updateHp();
    
}



// -----------------------------------------------------------------------------
// Collision stub (will be expanded later)
// -----------------------------------------------------------------------------
void Player::handleCollision()
{
}

void Player::setSpeed(float speed)
{
    m_speed = speed;
}



// Keep the sprite fully inside the window bounds
void Player::clampToWindow(const sf::Vector2u& windowSize)
{
    sf::FloatRect bounds = getGlobalBounds();
    sf::Vector2f  pos = getPosition();

    pos.x = std::clamp(pos.x,
        bounds.width / 2.f,
        static_cast<float>(windowSize.x) - bounds.width / 2.f);
    pos.y = std::clamp(pos.y,
        bounds.height / 2.f,
        static_cast<float>(windowSize.y) - bounds.height / 2.f);

   setPosition(pos);
}


void Player::setAttack(std::unique_ptr<AttackBehavior> attack)
{
    m_attack = std::move(attack);
}


void Player::setAniName(const std::string& name)
{
     m_aniName = name;
}

void Player::onStoneHit()
{
    moveSprite({ static_cast<float>(m_xdirHit) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<PlayerDeadState>());
    }
    m_state->onStoneHit(*this);
}

void Player::onBoxHit()
{
    moveSprite({ static_cast<float>(m_xdirHit) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<PlayerDeadState>());
    }
    m_state->onBoxHit(*this);
}

void Player::onHandsAttack()
{

    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<PlayerDeadState>());
    }
    m_state->onHandsAttack(*this);
    std::cout << typeid(*m_state).name() << "\n";
}

void Player::onExplosion()
{
    moveSprite({ static_cast<float>(m_direction.x) * 100, 0.f });
    if (m_hp <= 0) {
        m_hp = 0;
        m_potentialHp = 0;
        setState(std::make_unique<PlayerDeadState>());
    }
    m_state->onExplosion(*this);
}


bool Player::isAlive() const {
    return m_alive;
}

void Player::resetHP() {
    m_hp = PLAYER_HP;
    m_potentialHp = PLAYER_HP;
}