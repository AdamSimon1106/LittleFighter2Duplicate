#pragma once
#include <memory>
#include <iostream>
#include "SFML/Graphics.hpp"
#include"Management/ResourceManager.h"
#include "Management/Animation.h"
#include "PlayableObjectStates/PlayableObjectState.h"

#include <SFML/Window.hpp>



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
        case sf::Keyboard::Up:
            return PRESS_UP;
        case sf::Keyboard::Down:
            return PRESS_DOWN;
        case sf::Keyboard::RShift:
            return PRESS_JUMP;
        default:
            return NONE;
        }
    }

    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Return:
            return PRESS_ATTACK;
        case sf::Keyboard::Left:
            return RELEASE_LEFT;
        case sf::Keyboard::Right:
            return RELEASE_RIGHT;
        case sf::Keyboard::Down:
            return RELEASE_DOWN;
        case sf::Keyboard::Up:
            return RELEASE_UP;
        case sf::Keyboard::LShift:
            return ADD_OBJ;
        default:
            return NONE;

        }
    }
    return NONE;
}



class Player;
class PlayableObject;

class PlayerBaseState : public PlayableObjectState {
public:
    virtual ~PlayerBaseState() = default;
    void name() override {};
    void onHandsAttack(PlayableObject& player) override {};
    void onStoneHit(PlayableObject& player) override {};
    void onBoxHit(PlayableObject& player) override {};
    void onExplosion(PlayableObject& player) override {};

protected:
    Input m_input;
};
