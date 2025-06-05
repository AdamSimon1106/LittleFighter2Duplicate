// Player.cpp
#include "Gameplay/Player.h"
#include <algorithm>            // std::clamp


Player::Player(const sf::Texture& texture, float speed)
    : m_speed(speed)
{
    m_texture = texture;
    m_sprite.setTexture(m_texture);

    // Centre-origin so clamping works intuitively.
    auto sz = m_texture.getSize();
    m_sprite.setOrigin(static_cast<float>(sz.x) / 2.f,
        static_cast<float>(sz.y) / 2.f);
}

// Updates m_direction according to arrow keys
void Player::handleInput()
{
    m_direction = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  m_direction.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_direction.x = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    m_direction.y = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  m_direction.y = 1.f;

    // Normalise diagonal speed to remain constant.
    if (m_direction.x != 0.f && m_direction.y != 0.f)
    {
        constexpr float invSqrt2 = 0.70710678118f;       // 1 / ?2
        m_direction.x *= invSqrt2;
        m_direction.y *= invSqrt2;
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
}

// -----------------------------------------------------------------------------
// Draws the sprite
// -----------------------------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
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
