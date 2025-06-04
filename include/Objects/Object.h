#pragma once
#include "SFML/Graphics.hpp"

class Object {
public:
	virtual void handleCollision() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

};
