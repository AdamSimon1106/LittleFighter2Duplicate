// Player.cpp
#include "Gameplay/Player.h"
#include <algorithm>            // std::clamp
#include "PlayerStates/StandingState.h"
#include "PlayerStates/PlayerBaseState.h"

Player::Player(const sf::Vector2f pos, const std::string& name, float speed)
    : PlayableObject(pos, name), m_speed(speed), m_state(std::make_unique<StandingState>(RELEASE_RIGHT))
{
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
    move(dt);
    m_state->update(*this, dt);
    m_animation.update(dt);
    m_animation.applyToSprite(m_sprite);
    
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
    m_sprite.move(delta);
    if (m_heldObject)
    {
        sf::Vector2f offset(20.f, -100.f);
        m_heldObject->move(getPosition() + offset);
    }

}



void Player::setDiraction(Input input)
{
    switch (input)
    {
    case PRESS_LEFT:
        m_direction.x = -1.f;
        m_sprite.setScale(-1.f, 1.f);
        break;

    case PRESS_RIGHT:
        m_direction.x = 1.f;
        m_sprite.setScale(1.f, 1.f);
        break;

    case RELEASE_LEFT:
        if (m_direction.x < 0.f)
            m_direction.x = 0.f;
        break;

    case RELEASE_RIGHT:
        if (m_direction.x > 0.f)
            m_direction.x = 0.f;
        break;
    case PRESS_JUMP:
    case PRESS_UP:
        m_direction.y = -1.f;
        break;

    case RELEASE_UP:
       // if (m_direction.y < 0.f)
            m_direction.y = 0.f;
        break;

    case PRESS_DOWN:
        m_direction.y = 1.f;
        break;

    case RELEASE_DOWN:
      // if (m_direction.y > 0.f)
            m_direction.y = 0.f;
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

// -----------------------------------------------------------------------------
// Position helpers
// -----------------------------------------------------------------------------
void Player::setPosition(const sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

// -----------------------------------------------------------------------------
// Speed helpers
// -----------------------------------------------------------------------------
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
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    sf::Vector2f  pos = m_sprite.getPosition();

    pos.x = std::clamp(pos.x,
        bounds.width / 2.f,
        static_cast<float>(windowSize.x) - bounds.width / 2.f);
    pos.y = std::clamp(pos.y,
        bounds.height / 2.f,
        static_cast<float>(windowSize.y) - bounds.height / 2.f);

    m_sprite.setPosition(pos);
}

void Player::setAnimation(const Animation& anim)
{

    m_animation = anim;
    m_animation.reset();
    //m_animation.applyToSprite(m_sprite); 
}

void Player::setState(std::unique_ptr<PlayerBaseState> state)
{
    m_state = std::move(state);
    m_state->enter(*this);
}

void Player::pickUpObject(PickableObject& obj)
{
    m_heldObject = &obj;
    
        std::cout << " in Player::pickUpObject\n";
        m_heldObject->setPosition(m_sprite.getPosition() + sf::Vector2f(20.f, -30.f));
      
    
        
}



bool Player::isAlive() const {
    return m_alive;
}
