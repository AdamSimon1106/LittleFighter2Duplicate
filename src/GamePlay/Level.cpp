#include "Gameplay/Level.h"
#include <sstream>
#include "Management/ResourceManager.h"
#include "Factory/Factory.h"
#include "Management/CollisionHandling.h"
#include "GamePlay/Player.h"
#include "../include/UI/Background.h"




Level::Level(std::string background, sf::Vector2f screenSize) : 
    m_backgorund(screenSize, ResourceManager::instance().getTexture(background))
{
}

void Level::addSquad(std::string& squadLine)
{
    Squad newSquad;
     
    std::istringstream iss(squadLine);
    std::string token;

    while (iss >> token) {
        if (token.empty()) continue;

        char type = std::tolower(token[0]); // enemy type
        int count = std::stoi(token.substr(1)); // amount

        for (int i = 0; i < count; ++i) {
           
            auto enemy = Factory<Enemy>::create(std::string(1, type), sf::Vector2f(25.f*i, 50.f*i));

            if (enemy)
                newSquad.addEnemy(std::move(enemy));
        }
    }

    m_enemies.push_back(std::move(newSquad));
}

void Level::addPickableObjects(const std::string& objectLine)
{
    std::istringstream iss(objectLine);
    std::string token;

    while (iss >> token) {
        if (token.empty()) continue;

        char type = std::tolower(token[0]);

        auto obj = Factory<PickableObject>::create(std::string(1, type), sf::Vector2f(250.f, 500.f));
        if (obj)
        {
            std::cout << "in Level::addPickableObjects if (obj)\n";
            m_pickables.push_back(std::move(obj));
        }
    }
}

void Level::render(sf::RenderWindow& window)
{
    m_backgorund.draw(window, sf::RenderStates::Default);

    int index = static_cast<int>(m_phase);

    if (index < m_enemies.size()) {
        m_enemies[index].render(window); 
    }

    //render picObj
    for (auto& obj : m_pickables)
        obj->draw(window);

}

void Level::update(float dt)
{
    int index = static_cast<int>(m_phase);

    //just for demo need to pass player position
    if (index < m_enemies.size()) {
        m_enemies[index].update(sf::Vector2f(125.0f, 125.0f));
    }

    for (auto& obj : m_pickables)
        obj->update(dt);

    
}

bool Level::areAllEnemiesDefeated() const
{
    return false; // TODO: create logic to know if there is still living enemies
}

void Level::handleCollisionsWithPlayer(Player& player)
{
    for (const auto& obj : m_pickables)
    {
        if (player.collide(*obj)) {
            
            processCollision(player, *obj);
            
        }
    }
}
