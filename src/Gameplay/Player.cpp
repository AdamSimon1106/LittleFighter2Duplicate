// Player.cpp
#include "Gameplay/Player.h"
#include <algorithm>            // std::clamp
#include "PlayerStates/StandingState.h"
#include "PlayerStates/PlayerBaseState.h"

Player::Player(const sf::Texture& texture, float speed)
    : PlayableObject(texture), m_speed(speed), m_state(std::make_unique<StandingState>())
{
    //m_sprite.setTexture(m_texture);

    // Centre-origin so clamping works intuitively.
    auto sz = m_texture.getSize();
    m_sprite.setOrigin(static_cast<float>(sz.x) / 2.f,
        static_cast<float>(sz.y) / 2.f);

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

void Player::move()
{
    std::cout << "in player move\n";

    sf::Vector2f velocity = m_direction;

    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        constexpr float invSqrt2 = 0.70710678118f; // 1 / sqrt(2)
        velocity.x *= invSqrt2;
        velocity.y *= invSqrt2;
    }

    velocity.x *= m_speed;
    velocity.y *= m_speed;

    m_sprite.move(velocity);
}


void Player::setDiraction(Input input)
{
    std::cout << "in player setDirection\n";
    switch (input)
    {
    case PRESS_LEFT:
        m_direction.x = -1.f;
        break;
    case PRESS_RIGHT:
        m_direction.x = 1.f;
        break;
    case RELEASE_LEFT:
        if (m_direction.x < 0)
            m_direction.x = 0.f;
        break;
    case RELEASE_RIGHT:
        if (m_direction.x > 0)
            m_direction.x = 0.f;
        break;
    default:
        break;
    }
}

// -----------------------------------------------------------------------------
// Per-frame update – simple linear movement
// -----------------------------------------------------------------------------
void Player::update(float dt)
{
    sf::Vector2f delta(m_direction.x * m_speed * dt,
        m_direction.y * m_speed * dt);
    m_sprite.move(delta);

    //benny
    m_animation.update(dt);
    m_animation.applyToSprite(m_sprite);
}

// -----------------------------------------------------------------------------
// Draws the sprite
// -----------------------------------------------------------------------------
//void Player::draw(sf::RenderWindow& window)
//{
//    window.draw(m_sprite);
//}

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
    m_animation.applyToSprite(m_sprite); 
}

bool Player::isAlive() const {
    return m_alive;
}
