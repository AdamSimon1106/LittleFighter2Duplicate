#pragma once
#include "SFML/Graphics.hpp"

class GameManager; //forward declaration

class IState {
public:
	virtual ~IState() = default;
	IState(sf::RenderWindow& window, GameManager& manager) : m_window(window), m_manager(manager) {};
	virtual void update(sf::Time deltaTime) = 0;
	virtual void handleEvents(sf::Event& ev) = 0;
	virtual void render() = 0;

protected:
	sf::RenderWindow& m_window;
	GameManager& m_manager;
	bool m_switchState = false;
};
