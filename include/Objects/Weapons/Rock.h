#pragma once
#include "Objects/BigWeapon.h"

class Rock : public BigWeapon
{
public:
	Rock(const sf::Vector2f pos, const std::string& name);
	virtual void playAttack() override {};
	virtual void update(float dt) override;
private:
	static bool m_registered;
};