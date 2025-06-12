#include "Objects/Object.h"

Object::Object(const std::string& name)
{
	m_texture = &ResourceManager::instance().getTexture(name);
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(40.f, 40.f); // 80 / 2

}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

const sf::Texture* Object::getTexture()
{
	return m_texture;
}
