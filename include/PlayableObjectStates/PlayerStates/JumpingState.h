#pragma once
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"
#include "PlayableObjectStates/PlayerStates/JumpBasePhase/JumpPhaseBase.h"

class JumpingState : public PlayerBaseState
{
public:
	JumpingState(Input input);
	std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	void enter(PlayableObject& player) override;
	virtual void update(PlayableObject& player, float dt)override ;
	
	void onHandsAttack(PlayableObject& player) override {};
	void onStoneHit(PlayableObject& player) override {};
	void onExplosion(PlayableObject& player) override {};
private:
	float m_groundY;
	std::unique_ptr<JumpPhaseBase> m_phase;
};
