#pragma once
#include "States/IState.h"
#include "Management/ResourceManager.h"
#include <memory>
#include <vector>
#include "GamePlay/Level.h"
#include "Management/Controller.h"



class GameManager {
public:
	void switchState(IState& state);
	void readLevels(std::string path);

private:
	std::unique_ptr<IState> m_state;
	ResourceManager m_recourceManager;
	std::vector<Level> m_levels;
	Controller m_controller;
	
};
