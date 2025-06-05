#include "Gameplay/Level.h"
#include <sstream>
#include "Management/ResourceManager.h"
#include "Factory/Factory.h"

Level::Level(std::string background)
{
	//background
	const sf::Texture& bgTex = ResourceManager::instance().getTexture(background);
	m_backgroundSprite.setTexture(bgTex);

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
           
            auto enemy = Factory<Enemy>::create(std::string(1, type));

            if (enemy)
                newSquad.addEnemy(std::move(enemy));
        }
    }

    m_enemies.push_back(std::move(newSquad));
}

void Level::loadPickableObject(std::string& objectLine)
{
    std::istringstream iss(objectLine);
    std::string token;

    while (iss >> token) {
        if (token.empty()) continue;

        char type = std::tolower(token[0]);

        auto obj = Factory<PickableObject>::create(std::string(1, type));
        if (obj)
        {
            m_pickables.push_back(std::move(obj));
        }
    }
}

void Level::render(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);

    int index = static_cast<int>(m_faze);

    if (index < m_enemies.size()) {
        m_enemies[index].render(window); 
    }

    //render picObj

}
