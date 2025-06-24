#pragma once
#include "PlayerStates/PlayerBaseState.h"
#include "PlayerStates/JumpBasePhase/JumpPhaseBase.h"

class JumpingState : public PlayerBaseState
{
public:
	JumpingState(Input input);
	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
	virtual void update(Player& player, float dt)override ;
	
private:
	float m_groundY;
	std::unique_ptr<JumpPhaseBase> m_phase;
};
