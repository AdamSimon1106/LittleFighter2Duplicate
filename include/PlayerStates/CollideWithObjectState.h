#pragma once
#include "PlayerStates/PlayerBaseState.h"

class CollideWithObject : public PlayerBaseState
{
public:
	CollideWithObject(Input input);
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	virtual void enter(Player& player) override;

};