#pragma once

#include "PlayerStates/PlayerBaseState.h"

class WalkingState;

class StandingState : public PlayerBaseState
{
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	virtual void enter(Player& player) override;

};