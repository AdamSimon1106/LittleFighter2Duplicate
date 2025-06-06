#pragma once
#include "Gameplay/ComputerPlayer.h"

class Enemy : public ComputerPlayer{
public:
	Enemy(sf::Texture tex):ComputerPlayer(tex){ }
	
};
