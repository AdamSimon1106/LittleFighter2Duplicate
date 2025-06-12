#pragma once
#include "PlayerStates/PlayerBaseState.h"

class JumpingState : public PlayerBaseState
{
public:
	JumpingState(Input input);

	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
	virtual void update(Player& player, float dt)override ;
	
private:
	sf::Clock m_clock; 
	const float m_duration = 0.2f;

	
};
