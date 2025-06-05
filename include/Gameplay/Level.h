#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "Gameplay/Enemy.h"
#include "Objects/PickableObject.h"
// string\intאיך מייצגים שלב? 
//אולי std::vector<std::unique_ptr<Enemy>> m_enemies;
//std::vector<std::unique_ptr<PickableObject>> m_pickables;
//האם השלב עושה run, render, update?

class Level {
public:
	Level(int levelName);
	void run();
	void update();
	void render(sf::RenderWindow& window);



private:
	void loadLevel(const std::string& levelName);
	
	std::vector<Enemy> m_enemies;
	std::vector<PickableObject> m_pickable;
	

	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;

	std::string m_levelName;
};
