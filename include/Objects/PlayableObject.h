#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(const sf::Texture& tex) : Object(tex){}
	virtual void takeDamage(int damageAmount);


private:
	int m_hp;
	int m_energy;
};
