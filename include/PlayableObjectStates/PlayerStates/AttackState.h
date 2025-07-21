#pragma once
#include "Consts/Consts.h"
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"

class AttackState : public PlayerBaseState
{
public:
	AttackState() = default;

	std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	void enter(PlayableObject& player) override;
	virtual void update(PlayableObject& player, float dt) override;

	void onHandsAttack(PlayableObject& player) override;
	void onStoneHit(PlayableObject& player) override;
	void onBoxHit(PlayableObject& player) override;
	void onExplosion(PlayableObject& player) override;
private:
	sf::Clock m_clock;
	float m_attackDuration = ATTACK_DURATION;

};
