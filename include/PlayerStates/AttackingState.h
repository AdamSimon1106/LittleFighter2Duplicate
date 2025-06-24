#pragma once
#include "PlayerStates/PlayerBaseState.h"

class AttackingState : public PlayerBaseState
{
public:
	AttackingState() = default;

	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
private:

};
