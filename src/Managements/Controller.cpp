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
    m_players.push_back(std::make_shared<Player>(sf::Vector2f(50, 50), "davis_ani", 300.f));
    //      TODO: initialize HUD (m_stats)
    std::string enemiesLine = "b1 h1";
    m_level->addSquad(enemiesLine);

    std::string objectLine = "r";
    m_level->addPickableObjects(objectLine);
}

void Controller::handleInput(sf::Event ev)
{
    for (auto& player : m_players)
    {
        player->handleInput(ev);
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
       // ally->update(deltaTime);      TODO: update() in Ally
    }

    // Update the level itself (enemies, objects, etc.)
     m_level->update(deltaTime);
    //      TODO: create uptade() in Level - needs to update m_enemies!

    // Update HUD/stats with current data
    //m_stats.update(m_players, m_allies, *m_level);
    //      TODO: create uptade() in HUD
     m_level->handleCollisionsWithPlayer(*m_players.back());
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
   
    // Draw background, enemies, pickable objects, etc.
    m_level->render(m_window);

    // Draw all human players
    for (const auto& player : m_players)
    {
        //m_window.draw(*player);     TODO: draw() in Player
        player->draw(m_window);
    }

    // Draw AI allies
    for (const auto& ally : m_allies)
    {
        //m_window.draw(*ally);        TODO: draw() in Ally
        //ally->draw(m_window);
    }

    // Draw HUD
    //m_window.draw(m_stats);        TODO: draw() in HUD

    
}

//void Controller::updateAndRender(float deltaTime)
//{
//    if (m_levelFinished)
//        return;
//
//    handleInput(deltaTime);
//    updateWorld(deltaTime);
//    checkLevelEndConditions();
//    render();
//}

bool Controller::isLevelFinished() const
{
    return m_levelFinished;
}

bool Controller::didWin() const
{
    return m_playerWon;
}
