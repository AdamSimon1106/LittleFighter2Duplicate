#pragma once
#include "IState.h"
#include "Gameplay/Level.h"

class GameContoller; // Forward Declaration 

class InGameState : public IState {
public:
	InGameState(sf::RenderWindow& window, GameManager& manager, GameContoller& controller);
	void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	GameContoller& m_controller;

};
