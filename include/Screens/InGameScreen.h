#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Gameplay/Level.h"
#include "Gameplay/Player.h"
#include "Management/Controller.h"



class InGameScreen : public IScreen {
public:
	InGameScreen(sf::RenderWindow& window, GameManager& manager, std::shared_ptr<PlayerData> p, std::vector<std::shared_ptr<Ally>> allies);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	sf::Texture m_bgTexture;
	std::optional<Background> m_backGround;
	Button m_startButton;
	sf::Clock m_clock;
	Controller m_controller;


};
