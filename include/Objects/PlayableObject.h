#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(const sf::Texture& tex) : Object(tex){}
private:
	int m_hp;
	int m_energy;
};
