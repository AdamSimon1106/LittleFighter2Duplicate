#pragma once
#include "IState.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Gameplay/Level.h"
#include "Gameplay/Player.h"
#include "Management/Controller.h"



class InGameState : public IState {
public:
	InGameState(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	sf::Texture m_bgTexture;
	std::optional<Background> m_backGround;
	Button m_startButton;
    Level m_level;
	//Player m_player;
	sf::Clock m_clock;

	Controller m_controller;


};
