#pragma once

#include "IState.h"
#include "Management/Controller.h"
#include "Gameplay/Level.h"

class InGameState : public IState {
public:
	void update(sf::Time deltaTime) override;
    void handleEvents(sf::Event& ev) override;
	void render() override;
private:

};
