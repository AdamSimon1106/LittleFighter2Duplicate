#pragma once
#include "Objects/PlayableObject.h"
#include "SFML/Graphics.hpp"
#include "Gameplay/ComputerPlayer.h"
#include "Consts/Consts.h"
#include "PlayableObjectStates/ComputerPlayerState/IdleState.h"



class Ally : public ComputerPlayer {
public:
	Ally(const sf::Vector2f pos, const std::string& name, float speed = ALLY_SPEED);
	Ally(PlayerData p);
	void update(float dt) override; 
	void handleCollision() override;
	void resetHP();
	bool isAlive() const;
private:
	bool m_alive = true;
};
