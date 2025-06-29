#pragma once
#include "PlayerStates/PlayerBaseState.h"
#include "Objects/PickableObject.h"

class CollideWithObject : public PlayerBaseState
{
public:
	CollideWithObject(Input input, PickableObject* obj);
	virtual std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	virtual void enter(Player& player) override;
	virtual void update(Player& player, float dt)override;
private:
	PickableObject* m_obj;
	bool m_pickupPending = false;


};