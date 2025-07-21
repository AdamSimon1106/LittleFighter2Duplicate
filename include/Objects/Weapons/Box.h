#pragma once
#include "Objects/BigWeapon.h"
#include "Objects/ObjectStates/ObjectBaseState.h"

class Box : public BigWeapon
{
public:
	Box(const sf::Vector2f pos, const std::string& name);
	virtual void playAttack() override {};
	virtual void update(float dt) override;
	
private:
	static bool m_registered;
	
};