#pragma once
#pragma once
#include "Gameplay/Enemy.h"

class Hunter : public Enemy {
public:
	Hunter();
	virtual void handleCollision() override;
private:
	static bool m_registered;
};