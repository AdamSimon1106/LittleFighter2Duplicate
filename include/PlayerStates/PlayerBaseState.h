#pragma once
#include <memory>
#include <iostream>
#include "SFML/Graphics.hpp"
#include"Management/ResourceManager.h"
#include "Management/Animation.h"

class Player;

#include <SFML/Window.hpp>

enum Input
{
    PRESS_LEFT,
    PRESS_RIGHT,
    RELEASE_LEFT,
    RELEASE_RIGHT,
    PRESS_JUMP,
    PRESS_ATTACK,
};

inline Input getEventType(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            return PRESS_LEFT;
        case sf::Keyboard::Right:
            return PRESS_RIGHT;
        case sf::Keyboard::Space:
            return PRESS_JUMP;
        case sf::Keyboard::Z:
            return PRESS_ATTACK;
        
            
        }
    }

    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            return RELEASE_LEFT;
        case sf::Keyboard::Right:
            return RELEASE_RIGHT;
        
            
        }
    }
    return PRESS_JUMP;
}



class Player;

class PlayerBaseState {
public:
	virtual ~PlayerBaseState() = default;
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) = 0;
	virtual void enter(Player& player) = 0;
	virtual void update(Player& player, float dt) { };
	

protected:
	Input m_input;
};
