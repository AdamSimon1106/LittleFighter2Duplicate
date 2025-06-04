#pragma once
#include "SFML/Graphics.hpp"
#include "Management/GameManager.h"

class IState {
public:
	virtual void update(sf::RenderWindow &window) = 0;
	virtual void handleEvents(sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

private:
	GameManager* m_manager;
};
