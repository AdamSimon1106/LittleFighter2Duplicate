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
	void switchState(std::unique_ptr<IState> nextState);
	void readLevels(std::string path);
	void run();

private:
	std::unique_ptr<IState> m_currState;
	std::unique_ptr<IState> m_nextState = nullptr;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	ResourceManager m_recourceManager;
	std::vector<Level> m_levels;
	Controller m_controller;
	
};
