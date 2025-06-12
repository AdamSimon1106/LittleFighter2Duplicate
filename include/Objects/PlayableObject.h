#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(const std::string& name) : Object(name){}
	virtual void takeDamage(int damageAmount);

private:
	int m_hp;
	int m_energy;
};
