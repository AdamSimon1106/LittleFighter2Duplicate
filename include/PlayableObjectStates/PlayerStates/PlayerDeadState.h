#pragma once

#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"

class PlayerDeadState : public PlayerBaseState
{
public:
	PlayerDeadState() = default;

	virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	virtual void enter(PlayableObject& player) override;
	virtual void update(PlayableObject& player, float dt) override {};

	void onHandsAttack(PlayableObject& player) override {};
	void onBoxHit(PlayableObject& player) override {};
	void onStoneHit(PlayableObject& player) override {};
	void onExplosion(PlayableObject& player) override {};
};