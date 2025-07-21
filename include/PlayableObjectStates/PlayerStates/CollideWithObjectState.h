#pragma once
#include "PlayableObjectStates/PlayerStates/PlayerBaseState.h"
#include "Objects/PickableObject.h"

class CollideWithObject : public PlayerBaseState
{
public:
	CollideWithObject(Input input, std::shared_ptr<PickableObject> obj);
	virtual std::unique_ptr<PlayableObjectState> handleInput(Input input) override;
	virtual void enter(PlayableObject& player) override;
	virtual void update(PlayableObject& player, float dt)override;

	void onHandsAttack(PlayableObject& player) override;
	void onStoneHit(PlayableObject& player) override ;
	void onBoxHit(PlayableObject& player) override;
	void onExplosion(PlayableObject& player) override;
private:
	std::shared_ptr<PickableObject> m_obj;
	bool m_pickupPending = false;


};