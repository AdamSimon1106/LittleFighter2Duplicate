#include "Objects/Object.h"

Object::Object(sf::Texture tex)
{
	m_sprite.setTexture(tex);
}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}