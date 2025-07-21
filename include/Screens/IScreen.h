#pragma once
#include "SFML/Graphics.hpp"

class GameManager; 
class IScreen {
public:
	virtual ~IScreen() = default;
	IScreen(sf::RenderWindow& window, GameManager& manager) : m_window(window), m_manager(manager) {};
	virtual void update(sf::Time deltaTime) {};
	virtual void handleEvents(sf::Event& ev) = 0;
	virtual void render() = 0;

protected:
	sf::RenderWindow& m_window;
	GameManager& m_manager;
	bool m_switchState = false;
};
