#pragma once
#include "SFML/Graphics.hpp"
#include "Management/ResourceManager.h"
#include "Management/Animation.h"
#include "Factory/Factory.h"
#include "iostream"

class Object {
public:
	Object(const sf::Vector2f pos, const std::string& name);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	void draw(sf::RenderWindow& window) const;
	const sf::Texture* getTexture();
	void setAnimation(const Animation& anim);
	void update(float dt);
	bool collide(Object& other)const;
	sf::FloatRect getGlobalBounds();
protected:
	sf::Sprite m_sprite;
	const sf::Texture* m_texture = nullptr;

	Animation m_animation;
	
};
