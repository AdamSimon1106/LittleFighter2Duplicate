#pragma once
#include "IState.h"
#include "UI/Background.h"
#include "UI/Button.h"

class MenuState : public IState {
public:
	MenuState(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	sf::Texture m_bgTexture;
	std::optional<Background> m_backGround;
	Button m_startButton;
};
