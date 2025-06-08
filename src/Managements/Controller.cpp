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

