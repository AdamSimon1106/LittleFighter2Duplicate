#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gameplay/Enemy.h"
#include "Gameplay/Squad.h"
#include "Objects/PickableObject.h"
#include "UI/Background.h"
#include "Management/LevelLoader.h"
class Player;

enum class Phase { Phase1, Phase2, Phase3 };

class Level {
public:
	Level(std::string background, sf::Vector2f screenSize);
	void addSquad(std::string& squad);
	void addPickableObjects(const std::string& objectLine);
	void render(sf::RenderWindow& window);
	void update(float dt);
	bool areAllEnemiesDefeated() const;
	std::vector<std::shared_ptr<Enemy>> getAllEnemies();
	std::vector<std::shared_ptr<PickableObject>> getAllObjects();
	void handleCollisionsWithPlayer(PlayableObject& player);
	int numOfStages() { return m_enemies.size(); };
	
private:
	sf::Vector2f getRandomBoundedPosition(float xMin, float xMax, float yMin, float yMax);
	std::vector<Squad> m_enemies;
	std::vector<std::shared_ptr<PickableObject>> m_pickables;
	int m_phase = -1;
	Background m_backgorund;
};
