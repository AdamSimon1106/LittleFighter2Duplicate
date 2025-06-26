#pragma once
#include "Objects/Weapon.h"

class Rock : public Weapon
{
public:
	Rock(const sf::Vector2f pos, const std::string& name);
	virtual void handleCollision() {};
	virtual void playAttack() override;
	void update(float dt) override;
	void throwRock(int direction, float groundY, float speed = 200.f);
	
private:
	static bool m_registered;
	bool m_isFlying = false;
	sf::Vector2f m_velocity = { 0.f, 0.f };  
	float m_groundY = 0.f;  
	float m_gravity = 1000.f;  


};