#pragma once

#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"


class PlayerGotHitState : public PlayerBaseState
{
public:
	PlayerGotHitState() = default;
	virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	virtual void update(PlayableObject& player, float dt) override;
	virtual void enter(PlayableObject& player) override;

	void onHandsAttack(PlayableObject& player) override {};
	void onStoneHit(PlayableObject& player) override {};
	void onBoxHit(PlayableObject& player) override {};
	void onExplosion(PlayableObject& player) override {};
private:
	float m_recoveryTime = 0.15f;  // Time lying down before recovery
	float m_elapsedTime = 0.0f;
};