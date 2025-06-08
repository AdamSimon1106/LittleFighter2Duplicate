#pragma once
#include "Gameplay/ComputerPlayer.h"

class Enemy : public ComputerPlayer{
public:
	Enemy(const sf::Texture& tex):ComputerPlayer(tex){ }
	
};
