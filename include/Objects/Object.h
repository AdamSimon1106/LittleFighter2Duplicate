#pragma once
#include "SFML/Graphics.hpp"

class Object {
public:
	Object(sf::Texture tex);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	void draw(sf::RenderWindow& window) const;

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	
};
