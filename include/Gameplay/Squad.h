#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gameplay/Enemy.h"
//groop of enemies for every level faze
class Squad {
public:
	void draw(sf::RenderWindow& window);
	void update(float dt);
	
private:
	std::vector<Enemy> m_squad;

};