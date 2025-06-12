#pragma once
#include "Gameplay/ComputerPlayer.h"

class Enemy : public ComputerPlayer{
public:
	Enemy(const std::string& name):ComputerPlayer(name){ }
	virtual void update(/*float dt*/ const sf::Vector2f playerPos) = 0;
};
