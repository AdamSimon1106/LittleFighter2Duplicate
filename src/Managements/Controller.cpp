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
