#pragma once

#include "IState.h"
#include "Management/Controller.h"
#include "Gameplay/Level.h"

class InGameState : public IState {
public:
	virtual void update(sf::RenderWindow& window) override;
	virtual void handleEvents(sf::RenderWindow& window) override;
	virtual void render(sf::RenderWindow& window) override;
private:
	Controller& m_controller;
};
