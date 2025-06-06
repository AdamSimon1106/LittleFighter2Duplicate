#pragma once
#include "Gameplay/Enemy.h"

class Bandit : public Enemy {
public:
	Bandit();
	virtual void handleCollision() override;
private:
	static bool m_registered
};