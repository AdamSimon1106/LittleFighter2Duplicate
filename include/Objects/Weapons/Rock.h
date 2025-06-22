#pragma once
#include "Objects/Weapon.h"

class Rock : public Weapon
{
public:
	Rock(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	virtual void playAttack() override;
private:
	static bool m_registered;

};