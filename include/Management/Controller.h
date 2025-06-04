#pragma once
#include "Gameplay/Level.h"
#include "UI/HeadsUpDisplay.h"
#include "Gameplay/Player.h"
#include "Gameplay/Ally.h"
#include <vector>




class Controller {
public:
	void run();
private:
	Level m_level;
	HeadsUpDisplay m_stats;
	Player m_player;
	std::vector<Ally> m_allies;
};
