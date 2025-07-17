#pragma once
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"

class RunningState : public PlayerBaseState
{
public:
	RunningState(Input input);
	virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	virtual void enter(PlayableObject& player) override;
	virtual void update(PlayableObject& player, float dt) override {};

private:

	void onHandsAttack(PlayableObject& player) override {};
	void onStoneHit(PlayableObject& player) override {};
	void onExplosion(PlayableObject& player) override {};

	
};