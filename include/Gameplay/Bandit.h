#pragma once
#include "Gameplay/Enemy.h"

class Bandit : public Enemy {
public:
	Bandit(const sf::Vector2f pos);
	virtual void handleCollision() override;
	virtual void update(/*float dt*/ const sf::Vector2f playerPos) override;
	void move(const sf::Vector2f playerPos);
private:
	static bool m_registered;

	//used in move()
	sf::Vector2f m_direction;
	float m_attackRange = 60.f;
};