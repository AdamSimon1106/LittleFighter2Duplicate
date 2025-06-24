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
    PRESS_UP,
    PRESS_DOWN,
    RELEASE_UP,
    RELEASE_DOWN,
    PRESS_JUMP,
    PRESS_ATTACK,
    END_ATTACK,
    ADD_OBJ,
    NONE,
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
        case sf::Keyboard::Return:
            return PRESS_ATTACK;
        case sf::Keyboard::Up:
            return PRESS_UP;
        case sf::Keyboard::Down:
            return PRESS_DOWN; 
        case sf::Keyboard::RShift:
            return PRESS_JUMP;
        default:
            std::cout << "non pressed\n";
            return NONE;
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
        case sf::Keyboard::Down:
            return RELEASE_DOWN;
        case sf::Keyboard::Up:
            return RELEASE_UP;
        
        case sf::Keyboard::Return:
            return END_ATTACK;
        case sf::Keyboard::LShift:
            return ADD_OBJ;
        default:
            std::cout << "non pressed\n";
            return NONE;
            
        }
    }
    std::cout << "non pressed\n";
    return NONE;
}



class Player;

class PlayerBaseState {
public:
	virtual ~PlayerBaseState() = default;
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) = 0;
	virtual void enter(Player& player) = 0;
    virtual void update(Player& player, float dt) {};
	

protected:
	Input m_input;
};