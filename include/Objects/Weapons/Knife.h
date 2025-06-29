#pragma once
#include "Objects/Weapon.h"

class Knife : public Weapon
{
public:
	Knife(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	virtual void playAttack() override;
	virtual void move(const sf::Vector2f goal) override;
private:
	static bool m_registered;
	std::vector<sf::Vector2f> m_offsets = {
	{ 20.f, 30.f },  
	{ 25.f, 28.f }, 
	{ 22.f, 32.f } };

};