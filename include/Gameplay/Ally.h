#pragma once
#include "Objects/PlayableObject.h"
#include "SFML/Graphics.hpp"
#include "Gameplay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"



class Ally : public ComputerPlayer {
public:
	Ally(const std::string& name, float speed = 200.f);

	bool isAlive() const;
private:
	float m_speed;
	sf::Text m_name;
	bool m_alive = true;
};
