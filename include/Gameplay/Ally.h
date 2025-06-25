#pragma once
#include "Objects/PlayableObject.h"
#include "SFML/Graphics.hpp"
#include "Gameplay/ComputerPlayer.h"
#include "ComputerPlayerState/IdleState.h"



class Ally : public ComputerPlayer {
public:
	Ally(const sf::Vector2f pos, const std::string& name, float speed = 200.f);
	void update(float dt) override; 
	void handleCollision() override;

	bool isAlive() const;
private:
	//sf::Text m_name;
	bool m_alive = true;
};
