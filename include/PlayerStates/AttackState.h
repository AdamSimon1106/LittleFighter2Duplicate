#pragma once
#include "PlayerStates/PlayerBaseState.h"

class AttackState : public PlayerBaseState
{
public:
	AttackState() = default;

	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
	virtual void update(Player& player, float dt)override;
private:
	sf::Clock m_clock;
	float m_attackDuration = 1.0f;

};
