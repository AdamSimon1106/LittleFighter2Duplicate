#pragma once
#include "PlayerStates/PlayerBaseState.h"

class JumpingState : public PlayerBaseState
{
public:
	JumpingState() = default;

	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
	
private:
	sf::Clock m_clock; // ?? שעון פנימי
	const float m_duration = 0.2f;

	
};
