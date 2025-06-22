#pragma once
#include "Gameplay/ComputerPlayer.h"

class Enemy : public ComputerPlayer{
public:
	Enemy(const sf::Vector2f pos, const std::string& name):ComputerPlayer(pos, name){ }
	virtual void update(/*float dt*/ const sf::Vector2f playerPos) = 0;
};
