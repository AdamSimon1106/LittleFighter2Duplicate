#pragma once
#include "SFML/Graphics.hpp"
#include "Gameplay/ComputerPlayer.h"


class Ally : public ComputerPlayer{
public:
	bool isAlive() const;
private:
	sf::Text m_name;
	m_alive = true;
};
