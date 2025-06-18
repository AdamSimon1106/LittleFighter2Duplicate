#pragma once
#include "Objects/PlayableObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include<PlayerStates/PlayerBaseState.h>
#include "Objects/PickableObject.h"


class Player : public PlayableObject
{
public:
    explicit Player(const sf::Vector2f pos, const std::string& name, float speed = 200.f);

    void handleInput(sf::Event event);                 // Reads arrow-key state (?) m_direction
    void update(float dt);
    void move(float dt);                                // Moves position by m_direction * speed * dt
    void setDiraction(Input input);
               
    //void draw(sf::RenderWindow& window) override;/* Draws the sprite at current position */
    void handleCollision() override;    // Stub for future collision handling

    void setSpeed(float speed);
    float getSpeed() const;

    bool isAlive() const;

    /* Keep the player inside the window bounds */
    void clampToWindow(const sf::Vector2u& windowSize);

    /*void setAnimation(const Animation& anim);*/
    void setState(std::unique_ptr<PlayerBaseState> state);

    void pickUpObject(PickableObject& obj);
    void setAniName(const std::string& name);
private:
    float m_speed = 600.f;
    bool m_alive = true;
    sf::Vector2f m_direction{ 0.f,0.f };
    //sf::Text m_name;

    std::unique_ptr<PlayerBaseState> m_state;
    PickableObject* m_heldObject = nullptr;

    //maybe in base
    std::string m_aniName ;
    std::string m_currentAnimationName;
};
