#pragma once
#include "PlayerStates/PlayerBaseState.h"

enum class weaponType {
	Rock,
	Knife,
};

class WeaponHolding : public PlayerBaseState
{
public:
	WeaponHolding(Input input, weaponType weapon);
	std::unique_ptr<PlayerBaseState> handleInput(Input input) override;
	void enter(Player& player) override;
	virtual void update(Player& player, float dt)override;

private:
	weaponType m_weaponType;
};
