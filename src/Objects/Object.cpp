#include "Objects/Object.h"
#include <random>

Object::Object(const sf::Vector2f pos, const std::string& name)
{
	m_texture = &ResourceManager::instance().getTexture(name);
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(40.f, 80.f); 
	m_sprite.setPosition(pos);
}

Object::Object(std::shared_ptr<sf::Texture>textSheet)
{
	m_texture = textSheet.get();
	m_sprite.setTexture(*textSheet);
	m_sprite.setOrigin(40.f, 80.f);
	m_sprite.setPosition(sf::Vector2f(1000,800));
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
	m_sprite.setOrigin(m_animation.getCurrentSize().x / 2.f, m_animation.getCurrentSize().y);
	m_animation.reset();
}

void Object::setPosition(const sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

sf::FloatRect Object::buildMyRect() {
	sf::Vector2f dimensions = m_animation.getCurrentSize();
	float myX = getPosition().x - dimensions.x/2;
	float myY = getPosition().y - dimensions.y;
	sf::FloatRect rect = sf::FloatRect(myX, myY, dimensions.x, dimensions.y);
	return rect;		
}

void Object::update(float dt)
{
	sf::FloatRect box = buildMyRect();

	if (!m_bounds.contains(box)) {
		sf::Vector2f offset = getPosition() - sf::Vector2f(box.left, box.top);
		sf::Vector2f correctedTopLeft = m_bounds.clampPosition(box);
		setPosition(correctedTopLeft + offset);
	}
	m_animation.applyToSprite(m_sprite);

}


bool Object::collide(Object& other) const
{
	sf::FloatRect thisBounds = m_sprite.getGlobalBounds();
	sf::FloatRect otherBounds = other.getGlobalBounds();

	const float buffer = -20.f; 

	thisBounds.left -= buffer;
	thisBounds.top -= buffer;
	thisBounds.width += 2 * buffer;
	thisBounds.height += 2 * buffer;

	return thisBounds.intersects(otherBounds);
}

sf::FloatRect Object::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const
{

	return m_sprite.getPosition();

}

void Object::setSize(float scale)
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
	auto scale = m_sprite.getScale();
    float absX = std::abs(scale.x);
    m_sprite.setScale(side * absX, scale.y);
}

void Object::setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);

}

void Object::adjustBoundsToJump()
{
	m_bounds = BOUNDS_WITH_JUMP;
}
void Object::adjustBoundsBack()
{
	m_bounds = WORLD_BOUNDS;
}


sf::Vector2f Object::getSize() const
{
	return m_animation.getCurrentSize();
}

sf::Sprite& Object::getSprite() {
	return m_sprite;
}


sf::Vector2f Object::getGeometricCenter() const {
	return {
		getPosition().x,
		getPosition().y - getSize().y / 2.f
	};
}

sf::Vector2f Object::getRandomYPosition(float xPos, float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);

	float y = dist(gen);
	return sf::Vector2f(xPos, y);
}