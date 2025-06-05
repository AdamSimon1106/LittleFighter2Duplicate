#pragma once
#include "Objects/PlayableObject.h"
#include <SFML/Graphics.hpp>


class Player : public PlayableObject
{
public:
    explicit Player(const sf::Texture& texture, float speed = 200.f);

    void handleInput();                 // Reads arrow-key state (?) m_direction
    void update(float dt);              // Moves position by m_direction*speed*dt
    void draw(sf::RenderWindow& window) override;/* Draws the sprite at current position */
    void handleCollision() override;    // Stub for future collision handling

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

    void setSpeed(float speed);
    float getSpeed() const;

    /* Keep the player inside the window bounds */
    void clampToWindow(const sf::Vector2u& windowSize);

private:
    float m_speed = 600.f;
    sf::Vector2f m_direction{ 0.f,0.f };
    //sf::Text m_name;

};
