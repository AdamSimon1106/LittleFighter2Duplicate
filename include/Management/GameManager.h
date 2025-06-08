#pragma once
#include "States/IState.h"
#include "Management/ResourceManager.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GamePlay/Level.h"
#include "Management/Controller.h"

class GameManager {
public:
	GameManager();
	void switchState(std::unique_ptr<IState> nextState);
	void readLevels(std::string path);
	void run();

private:
	sf::RenderWindow m_window;
	std::vector<Level> m_levels;
	std::unique_ptr<IState> m_currState;
	std::unique_ptr<IState> m_nextState = nullptr;
	
};
