#pragma once

#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"


class WalkingState;

class StandingState : public PlayerBaseState
{
public:
	StandingState(Input input);
	virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	virtual void update(PlayableObject& player, float dt) override {};
	virtual void enter(PlayableObject& player) override;
	
	void onHandsAttack(PlayableObject& player) override;
	void onStoneHit(PlayableObject& player) override;
	void onBoxHit(PlayableObject& player) override;	
	void onExplosion(PlayableObject& player) override;
};