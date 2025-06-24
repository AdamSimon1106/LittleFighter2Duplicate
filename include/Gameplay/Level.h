#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gameplay/Enemy.h"
#include "Gameplay/Squad.h"
#include "Objects/PickableObject.h"
#include "UI/Background.h"
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
	void handleCollisionsWithPlayer(Player& player);

	
private:
	std::vector<Squad> m_enemies;
	std::vector<std::unique_ptr<PickableObject>> m_pickables;
	Phase m_phase = Phase::Phase1;
	Background m_backgorund;
};
