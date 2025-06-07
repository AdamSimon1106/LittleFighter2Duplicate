#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Management/GameManager.h"
#include "States/IState.h"
#include "States/InGameState.h"
#include "States/WelcomeState.h"
#include "GamePlay/Level.h" 

GameManager::GameManager() : m_window(sf::VideoMode(500, 500), "Little Fighter 2"),
                             m_currState(std::make_unique<InGameState>(m_window, *this)
{}


void GameManager::switchState(std::unique_ptr<IState> nextState)
{
    m_nextState = std::move(nextState);
}

void GameManager::readLevels(std::string path)
{
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue; // remove empty lines from beggining

        // background
        Level level(line);


        while (std::getline(file, line)) {
            // objects
            if (line.rfind("Objects: ", 0) == 0) {
                level.addObjects(line.substr(9)); // הורדת "Objects: "
                break; // זה סוף השלב
            }
            // squads
            if (!line.empty())
                level.addSquad(line);
        }

        m_levels.push_back(std::move(level));
    }

}