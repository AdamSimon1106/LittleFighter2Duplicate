#pragma once
#include "PlayerStates/PlayerBaseState.h"

class WalkingState : public PlayerBaseState
{
public:
	WalkingState(Input input);
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	virtual void enter(Player& player) override;
};