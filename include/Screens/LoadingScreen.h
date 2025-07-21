#pragma once
#include "IScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/DataLoader.h"
#include "Management/LevelLoader.h"


class LoadingScreen: public IScreen {
public:
	LoadingScreen(sf::RenderWindow& window, GameManager& manager);
	void update(sf::Time deltaTime) override;
	void handleEvents(sf::Event& ev) override;
	void render() override;
private:
	std::optional<Background> m_backGround;
	Button m_startButton;
	sf::Text m_currentlyLoading;
	sf::Text m_chienese;
	sf::Font m_font;
	LevelLoader m_levelsLoader;
	DataLoader m_dataLoader;
	bool m_canSwitchScreen = false;
};
