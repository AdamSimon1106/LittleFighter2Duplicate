#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gameplay/Enemy.h"
#include "Gameplay/Squad.h"
#include "Objects/PickableObject.h"
class Player;

enum class Faze { Faze1, Faze2, Faze3 };

class Level {
public:
	Level(std::string background);
	void addSquad(std::string& squad);
	void addPickableObjects(const std::string& objectLine);
	void render(sf::RenderWindow& window);
	void update(float dt);
	bool areAllEnemiesDefeated() const;
	//std::vector<Enemy*> getAllEnemies();
	//std::vector<PickableObject*> getAllObjects();
	void handleCollisionsWithPlayer(Player& player);

	
private:
	std::vector<Squad> m_enemies;
	std::vector<std::unique_ptr<PickableObject>> m_pickables;
	Faze m_faze = Faze::Faze1;
	sf::Sprite m_backgroundSprite;
};
	};
