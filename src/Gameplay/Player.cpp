#include "Gameplay/Player.h"
#include <algorithm>            // std::clamp
#include "PlayerStates/StandingState.h"
#include "PlayerStates/PlayerBaseState.h"
#include "Management/AnimationManager.h"

Player::Player(const sf::Vector2f pos, const std::string& name, float speed)
    : PlayableObject(pos, name), m_speed(speed), m_state(std::make_unique<StandingState>(RELEASE_RIGHT))
{
	m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
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
    if (m_currentAnimationName != m_aniName + m_strategyName) {
        setAnimation(AnimationManager::getAnimation(m_aniName + m_strategyName, getTexture()));
        m_currentAnimationName = m_aniName + m_strategyName;
    }
    move(dt);
    m_state->update(*this, dt);
    updateAnimation(dt);
    apllySprite();
    
}

void Player::move(float dt)
{
    sf::Vector2f velocity = m_direction;

    // Normalize diagonal movement (to prevent faster diagonal movement)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        constexpr float invSqrt2 = 0.70710678118f;
        velocity.x *= invSqrt2;
        velocity.y *= invSqrt2;
    }

    // Apply speed and delta time
    sf::Vector2f delta(velocity.x * m_speed * dt,
        velocity.y * m_speed * dt);  
    moveSprite(delta);
    if (m_heldObject)
    {
        m_heldObject->move(getPosition());
    }

}



void Player::setDiraction(Input input)
{
    std::cout << input << "\n";
    switch (input)
    {
    case PRESS_LEFT:
        m_direction.x = -1.f;
       setScale(-1);
        break;
    case PRESS_RIGHT:
        m_direction.x = 1.f;
        setScale(1);
        break;
    case RELEASE_LEFT:
    case RELEASE_RIGHT:
        m_direction.x = 0.f;
        break;
    case PRESS_JUMP:
    case PRESS_UP:
        m_direction.y = -1.f;
        break;
    case PRESS_FALLING:
    case RELEASE_UP:
    case RELEASE_DOWN:
            m_direction.y = 0.f;
        break;
    case PRESS_DOWN:
        m_direction.y = 1.f;
        break;
    default:
        break;
    }
}

// -----------------------------------------------------------------------------
// Collision stub (will be expanded later)
// -----------------------------------------------------------------------------
void Player::handleCollision()
{
    // TODO; Not for now. (must have to compile properly)
}

void Player::setSpeed(float speed)
{
    m_speed = speed;
}

float Player::getSpeed() const
{
    return m_speed;
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

void Player::setState(std::unique_ptr<PlayerBaseState> state)
{
    m_state = std::move(state);
    m_state->enter(*this);
}

void Player::setAttack(std::unique_ptr<AttackBehavior> attack)
{
    m_attack = std::move(attack);
}

void Player::pickUpObject(PickableObject* obj)
{
    m_heldObject = obj;
    //just for expirience. must do it nice
    m_strategyName = obj->getName();
    auto attack = Factory<AttackBehavior>::createAttackBehavior(m_strategyName, m_heldObject, this);
    if (attack)
    {
        m_attack = std::move(attack);
    }


    std::cout << m_aniName + m_strategyName << "\n";
    std::cout << " in Player::pickUpObject\n";
}

void Player::setAniName(const std::string& name)
{
     m_aniName = name;
}

void Player::setStrategyName(const std::string& name)
{
    m_strategyName = name;
}

void Player::attack()
{
   
    if (m_attack)
    {
        std::cout << "player attack\n";
        m_attack->attack();
    }
	//std::cout << m_heldObject->getName() << "\n";
    if (m_heldObject)
    {
        std::cout << "in player attack detuch object\n";
        m_heldObject = nullptr;
		
        m_attack = Factory<AttackBehavior>::createAttackBehavior("h", nullptr, this);
    }
    

}

bool Player::isHoldingWaepon(PickableObject* obj) const
{
	return m_heldObject != nullptr;
}

bool Player::isAlive() const {
    return m_alive;
}