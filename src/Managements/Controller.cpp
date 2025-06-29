#include "Management/Controller.h"
#include "Gameplay/Level.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <utility>
#include <iostream>

Controller::Controller(sf::RenderWindow& window,
    std::unique_ptr<Level> level,
    std::vector<std::shared_ptr<Player>> players,
    std::vector<std::shared_ptr<Ally>> allies)
    : m_window(window),
    m_level(std::move(level)),
    m_players(std::move(players)),
    m_allies(std::move(allies))
{   
    AnimationManager::loadAnimations();
    // add pickable (rock)
    std::string objectLine = "r r k";
    m_level->addPickableObjects(objectLine);
    // add enemies (one bandit)
    std::string sq = "b3";
    m_level->addSquad(sq);

    m_enemies = m_level->getAllEnemies();
    m_pickables = m_level->getAllObjects();
    // creating user's player
    m_players.push_back(std::make_shared<Player>(sf::Vector2f(1000, 800), "davis_ani", 320.f));
    // creating ally
    auto ally = std::make_shared<Ally>(sf::Vector2f(800, 40), "davis_ani", 100.f);
    auto allyTwo = std::make_shared<Ally>(sf::Vector2f(900, 700), "davis_ani", 100.f);
    auto allyThree = std::make_shared<Ally>(sf::Vector2f(380, 580), "davis_ani", 100.f);

    m_allies.push_back(ally);
    m_allies.push_back(allyTwo);
    m_allies.push_back(allyThree);


    updateComputerPlayerTargets();
    auto target = m_enemies[0]->getTarget();

    //      TODO: initialize HUD (m_stats)
    //std::string enemiesLine = "b1 h1";
    //m_level->addSquad(enemiesLine);
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
       ally->update(deltaTime);      //TODO: update() in Ally
    }
    for (auto& enemy : m_enemies)
    {
        enemy->update(deltaTime);
    }
    for (auto& obj : m_pickables)
    {
        obj->update(deltaTime);
    }

    updateComputerPlayerTargets();

    // Update the level itself (enemies, objects, etc.)
     //m_level->update(deltaTime);
    //      TODO: create uptade() in Level - needs to update m_enemies!

    // Update HUD/stats with current data
    //m_stats.update(m_players, m_allies, *m_level);
    //      TODO: create uptade() in HUD
    m_level->handleCollisionsWithPlayer(*m_players.back()); // currently through level, need to transfer into controller

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

        ally->draw(m_window);
    }

    for (const auto& enemy : m_enemies)
    {

        enemy->draw(m_window);
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

void Controller::updateComputerPlayerTargets() {

    // Update targets for allies (their enemies are the enemies from Level)
    for (auto& ally : m_allies) {
        if (!ally || !ally->needsEnemyTracking())
            continue;

        Enemy* closest = nullptr;
        Enemy* freeClosest = nullptr;
        float closestDist = std::numeric_limits<float>::max();
        float freeDist = closestDist;

        for (Enemy* enemy : m_enemies) {
            //std::cout << "ally " << ally->getPosition().x << "," << ally->getPosition().y << std::endl;
            //std::cout << "enemy " << enemy->getPosition().x << "," << enemy->getPosition().y << std::endl;

            float dist = distanceBetween(ally->getPosition(), enemy->getPosition());
            if (dist < closestDist) {
                closestDist = dist;
                closest = enemy;
            }
            if (!enemy->isAttacked() && dist < freeDist) {
                freeDist = dist;
                freeClosest = enemy;
            }

        }
        if (freeClosest) {
            ally->setTargetEnemy(freeClosest);
        }
        else if (closest)
            ally->setTargetEnemy(closest);
    }

    // Update targets for enemies (their enemies are players and allies)
    for (Enemy* enemy : m_enemies) {
        if (!enemy || !enemy->needsEnemyTracking())
            continue;

        PlayableObject* closest = nullptr;
        PlayableObject* freeClosest = nullptr;
        float closestDist = std::numeric_limits<float>::max();
        float freeDist = closestDist;


        //std::cout << "m_allies size: " << m_allies.size() << std::endl;

        // Check all allies
        for (auto& ally : m_allies) {
            float dist = distanceBetween(enemy->getPosition(), ally->getPosition());
            //std::cout << "[DEBUG] candidate ally, dist: " << dist << std::endl;

            if (dist < closestDist) {
                closestDist = dist;
                closest = ally.get();
            }
            if (!ally->isAttacked() && dist < freeDist) {
                freeDist = dist;
                freeClosest = ally.get();
            }
        }

        // Check all players
        for (auto& player : m_players) {
            float dist = distanceBetween(enemy->getPosition(), player->getPosition());
            if (dist < closestDist) {
                closestDist = dist;
                closest = player.get();
            }
            if (!player->isAttacked() && dist < freeDist) {
                freeDist = dist;
                freeClosest = player.get();
            }
        }
        if (freeClosest) {
            enemy->setTargetEnemy(freeClosest);
        }
        else if (closest)
            enemy->setTargetEnemy(closest);
    }
}



bool Controller::isLevelFinished() const
{
    return m_levelFinished;
}

bool Controller::didWin() const
{
    return m_playerWon;
}


// Calculates the Euclidean distance between two 2D points
float Controller::distanceBetween(sf::Vector2f a, sf::Vector2f b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

