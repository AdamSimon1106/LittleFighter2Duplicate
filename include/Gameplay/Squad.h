#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gameplay/Enemy.h"

// group of enemies for every level phaze
class Squad {
public:
	void render(sf::RenderWindow& window);
	void update(float dt);
	void addEnemy(std::unique_ptr<Enemy> enemy);

	std::vector<std::shared_ptr<Enemy>>& getEnemies();

	
private:
	std::vector<std::shared_ptr<Enemy>> m_squad;


};