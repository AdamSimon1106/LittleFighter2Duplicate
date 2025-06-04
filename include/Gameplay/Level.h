#pragma once
#include "Gameplay/Enemy.h"
#include <vector>
#include "SFML/Graphics.hpp"
class Level {
public:

private:
	std::vector<Enemy> m_enemies;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
};
