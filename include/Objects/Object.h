#pragma once
#include "SFML/Graphics.hpp"
#include "Management/ResourceManager.h"
#include "Management/Animation.h"

class Object {
public:
	Object(const std::string &name);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	void draw(sf::RenderWindow& window) const;
	const sf::Texture* getTexture();
protected:
	sf::Sprite m_sprite;
	const sf::Texture* m_texture = nullptr;

	Animation m_animation;
	
};
