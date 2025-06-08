#include "Management/Controller.h"
#include <SFML/Window.hpp>
#include <utility>

Controller::Controller(sf::RenderWindow& window,
    std::unique_ptr<Level> level,
    std::vector<std::shared_ptr<Player>> players,
    std::vector<std::shared_ptr<Ally>> allies)
    : m_window(window),
    m_level(std::move(level)),
    m_players(std::move(players)),
    m_allies(std::move(allies))
{
    // TODO: initialize HUD (m_stats)
}

void Controller::handleInput()
{
    for (auto& player : m_players)
    {
        player->handleInput();
    }
}

void Controller::updateWorld(float deltaTime)
{
    // Update all human-controlled players
    for (auto& player : m_players)
    {
        player->update(deltaTime);
    }

    // Update all AI-controlled allies
    for (auto& ally : m_allies)
    {
       // ally->update(deltaTime);
    }

    // Update the level itself (enemies, objects, etc.)
    // m_level->update(deltaTime);
    // TODO: create uptade func in class Level - needs to update m_enemies!

    // Update HUD/stats with current data
    //m_stats.update(m_players, m_allies, *m_level);
    // TODO: create uptade func in  class HUD

}


void Controller::checkLevelEndConditions()
{
    if (m_level->areAllEnemiesDefeated())
    {
        m_levelFinished = true;
        m_playerWon = true;
        return;
    }

    bool allPlayersDefeated = true;
    for (const auto& player : m_players)
    {
        if (player->isAlive())  
        {
            allPlayersDefeated = false;
            break;
        }
    }
    for (const auto& ally : m_allies)
    {
        if (ally->isAlive())
        {
            allPlayersDefeated = false;
            break;
        }
    }

    if (allPlayersDefeated)
    {
        m_levelFinished = true;
        m_playerWon = false;
    }
}

void Controller::render()
{
    m_window.clear();

    // Draw background, enemies, pickable objects, etc.
    m_level->render(m_window);

    // Draw all human players
    for (const auto& player : m_players)
    {
        //m_window.draw(*player);   TODO: draw() in Player
    }

    // Draw AI allies
    for (const auto& ally : m_allies)
    {
        //m_window.draw(*ally);     TODO: draw() in Ally
    }

    // Draw HUD
    //m_window.draw(m_stats); TODO: draw() in HUD

    m_window.display();
}

void Controller::updateAndRender(float deltaTime)
{
    if (m_levelFinished)
        return;

    handleInput();
    updateWorld(deltaTime);
    checkLevelEndConditions();
    render();
}

