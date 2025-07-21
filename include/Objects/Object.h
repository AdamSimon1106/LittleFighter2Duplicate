#pragma once
#include "SFML/Graphics.hpp"
#include "Management/ResourceManager.h"
#include "Management/Animation.h"
#include "Management/AnimationManager.h"
#include "Factory/Factory.h"
#include "Management/WorldBounds.h"
#include "Consts/Consts.h"
#include "iostream"

class Object {
public:
	Object(const sf::Vector2f pos, const std::string& name);
	Object(std::shared_ptr<sf::Texture>textSheet);
	virtual ~Object() = default;
	virtual void handleCollision() = 0;
	virtual void update(float dt);
	
	void setAnimation(const Animation& anim);
	void setPosition(const sf::Vector2f pos);

	sf::FloatRect getGlobalBounds() const;
	const sf::Texture* getTexture();
	void draw(sf::RenderWindow& window) const;
	bool collide(Object& other) const;
	sf::FloatRect buildMyRect();
	sf::Vector2f getPosition() const;
	void setSize(float scale);
	sf::Vector2f getGeometricCenter() const;
	virtual sf::Vector2f getRandomYPosition(float xPos, float min, float max);
	virtual void adjustBoundsToJump();
	virtual void adjustBoundsBack();
protected:
	void setScale(int side);
	void setOrigin(float x, float y);
	sf::Vector2f getSize() const;
	sf::Sprite& getSprite();
	void updateAnimation(float dt);
	void apllySprite();
	void moveSprite(sf::Vector2f pos);

private:
	const sf::Texture* m_texture = nullptr;
	sf::Sprite m_sprite;
	WorldBounds m_bounds = WORLD_BOUNDS; // x of leftUpCorner, y of leftUpCorner, width, height  
	Animation m_animation;
};
