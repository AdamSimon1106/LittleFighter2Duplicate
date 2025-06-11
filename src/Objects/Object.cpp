#include "Objects/Object.h"

Object::Object(const sf::Texture& tex)
{
	m_sprite.setTexture(tex);
	m_sprite.setOrigin(40.f, 40.f); // 80 / 2

}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}