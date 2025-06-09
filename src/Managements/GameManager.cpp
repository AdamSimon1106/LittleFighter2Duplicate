#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Management/GameManager.h"
#include "Management/Controller.h"
#include "States/IState.h"
#include "States/InGameState.h"
#include "States/WelcomeState.h"
#include "GamePlay/Level.h" 
#include<iostream>

GameManager::GameManager() : m_window(sf::VideoMode(1000, 800), "Little Fighter 2")
{
    m_currState = std::make_unique<WelcomeState>(m_window, *this);
}

void GameManager::run()
{
    std::cout << "Running game, m_currState: " << m_currState.get() << std::endl;
    sf::Clock clock;
    while (m_window.isOpen())
    {
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
            m_currState->handleEvents(ev);

            sf::Time deltaTime = clock.restart();

            m_currState->update(deltaTime);
            if (m_nextState)
            {
                m_currState = std::move(m_nextState);
            }

        }
        
        m_window.clear();
        m_currState->render();
        m_window.display();
    }
}

void GameManager::switchState(std::unique_ptr<IState> nextState)
{
    m_nextState = std::move(nextState);
}
/*
void GameManager::readLevels(std::string path)
{
    std::ifstream file(path);
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue; // remove empty lines from beggining

        Level level(line);

        while (std::getline(file, line)) {
            // objects
            if (line.rfind("Objects: ", 0) == 0) {
                level.addPickableObjects(line.substr(9));
                break; 
            }
            // squads
            if (!line.empty())
                level.addSquad(line);
        }

        m_levels.push_back(std::move(level));
    }
**/