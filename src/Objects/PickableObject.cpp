#include "Objects/PickableObject.h"

PickableObject::PickableObject(const sf::Vector2f pos, const std::string& name)
	:Object(pos, name)
{
}

void PickableObject::move(sf::Vector2f goal)
{
	m_goalPosition = goal;
	setPosition(m_goalPosition);
	
}
