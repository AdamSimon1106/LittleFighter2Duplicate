#include "Objects/Object.h"

Object::Object(const sf::Vector2f pos, const std::string& name)
{
	m_texture = &ResourceManager::instance().getTexture(name);
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(40.f, 80.f); // 80 / 2
	m_sprite.setPosition(pos);
	//std::cout << "[Object] name: " << name
		//<< ", initial pos: (" << pos.x << ", " << pos.y << ")" << std::endl;

}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

const sf::Texture* Object::getTexture()
{
	return m_texture;
}

void Object::setAnimation(const Animation& anim)
{
	m_animation = anim;
	m_animation.reset();
}

void Object::setPosition(const sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Object::update(float dt)
{	
	//m_animation.update(dt);
	m_animation.applyToSprite(m_sprite);
}

bool Object::collide(Object& other) const
{
	return m_sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect Object::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const
{

	return m_sprite.getPosition();

}

void Object::setScale(float scale)
{
	m_sprite.setScale(scale, scale);
}



void Object::updateAnimation(float dt)
{
	m_animation.update(dt);
}

void Object::apllySprite()
{
	m_animation.applyToSprite(m_sprite);
}

void Object::moveSprite(sf::Vector2f pos)
{
	m_sprite.move(pos);
}

void Object::setScale(int side)
{
	m_sprite.setScale(side, 1);
}

sf::Sprite& Object::getSprite() {
	return m_sprite;
}

const sf::Sprite& Object::getSprite() const {
	return m_sprite;
}
