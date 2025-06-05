#include "Objects/Object.h"

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}