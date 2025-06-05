#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "Gameplay/Enemy.h"
#include "Gameplay/Squad.h"
#include "Objects/PickableObject.h"
// string\intאיך מייצגים שלב? 
//אולי std::vector<std::unique_ptr<Enemy>> m_enemies;
//std::vector<std::unique_ptr<PickableObject>> m_pickables;
//האם השלב עושה run, render, update?

enum class Faze { Faze1, Faze2, Faze3 };

class Level {
public:
	Level(std::string background);
	void addSquad(std::string& squad);
	void run();
	void update();
	void render(sf::RenderWindow& window);



private:
	void loadLevel(const std::string& levelName);
	
	std::vector<Squad> m_enemies;
	std::vector<PickableObject> m_pickable;
	
	Faze m_faze = Faze::Faze1;
	sf::Sprite m_backgroundSprite;
	std::string m_levelName;
};
