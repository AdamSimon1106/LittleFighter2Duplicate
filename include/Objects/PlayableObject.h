#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(sf::Vector2f pos, const std::string& name) : Object(pos, name){}
	/*virtual void takeDamage(int damageAmount);
	virtual void update(float dt) = 0;
	virtual float getSpeed() const;
	virtual void move(const sf::Vector2f& delta);*/


protected:
	int m_hp;
	int m_energy;
	float m_speed;
};
