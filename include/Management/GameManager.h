#pragma once
#include "Screens/IScreen.h"
#include "Management/ResourceManager.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GamePlay/Level.h"
#include "Management/Controller.h"

class GameManager {
public:
	GameManager();
	void switchScreen(std::unique_ptr<IScreen> nextState);
	void run();

private:
	sf::RenderWindow m_window;
	std::unique_ptr<IScreen> m_currScreen;
	std::unique_ptr<IScreen> m_nextScreen = nullptr;
	
};
