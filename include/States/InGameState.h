#pragma once
#include "IState.h"
#include "Gameplay/Level.h"
#include <SFML/Graphics.hpp>
#include "Management/Controller.h"

class GameManager; //forward declaration

class InGameState : public IState {
public:
	InGameState(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	GameManager& m_gameManager;
	Controller m_controller;
};
