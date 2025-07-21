#pragma once
#include "Objects/PlayableObject.h"
#include "SFML/Graphics.hpp"
#include "Gameplay/ComputerPlayer.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"

class Enemy : public ComputerPlayer{
public:
	Enemy(const sf::Vector2f pos, const std::string& name, float speed = 20.f);
	void update(float dt) override;
	void handleCollision() override;
	void resetHP();
	bool isAlive() const; 
private:
	bool m_alive = true;
	


};
