#pragma once
#include "Objects/Object.h"

class PlayableObject : public Object{
public:
	PlayableObject(const std::string& name) : Object(name){}
private:
	int m_hp;
	int m_energy;
};
