#pragma once
#include "Objects/Weapon.h"

class Knife : public Weapon
{
public:
	Knife(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	virtual void playAttack() override;
private:
	static bool m_registered;

};