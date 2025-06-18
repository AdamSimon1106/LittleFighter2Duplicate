#pragma once
#include "Objects/Object.h"

class PickableObject : public Object{
public:
	PickableObject(const sf::Vector2f pos, const std::string& name);
	
	void move(sf::Vector2f goal);
private:
	sf::Vector2f m_goalPosition;
};
