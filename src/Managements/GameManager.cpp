#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Management/GameManager.h"
#include "GamePlay/Level.h" 
#include "States/InGameState.h"

void GameManager::run()
{
    readLevels("levels.txt");
    m_controller.run(); // Eventually needs to be preformed through InGameState
}

void GameManager::switchState(IState& state)
{
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
                level.addPickableObjects(line.substr(9)); // הורדת "Objects: "
                break; // זה סוף השלב
            }
            // squads
            if (!line.empty())
                level.addSquad(line);
        }

        m_levels.push_back(std::move(level));
    }

}