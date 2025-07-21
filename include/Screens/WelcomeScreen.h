#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"

class WelcomeScreen : public IScreen {
public:
	WelcomeScreen(sf::RenderWindow& window, GameManager& manager);
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	std::optional<Background> m_backGround;
	Button m_startButton;	
};
