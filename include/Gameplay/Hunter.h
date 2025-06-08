#pragma once
#pragma once
#include "Gameplay/Enemy.h"

class Hunter : public Enemy {
public:
	Hunter();
	virtual void handleCollision() override;
	virtual void update(/*float dt*/ const sf::Vector2f playarPos) override {};
private:
	static bool m_registered;
};