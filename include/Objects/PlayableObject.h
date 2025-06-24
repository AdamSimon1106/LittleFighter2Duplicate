#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(sf::Vector2f pos, const std::string& name) : Object(pos, name){}
	//virtual void takeDamage(int damageAmount);


private:
	int m_hp;
	int m_energy;
};
