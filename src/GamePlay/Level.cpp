#include "Gameplay/Level.h"
#include <sstream>

Level::Level(std::string background)
{
	//background
	sf::Texture& bgTex = ResourceManager::instance().getTexture(background);
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
            std::unique_ptr<Enemy> enemy = nullptr;

            switch (type) {
            case 'p':
                enemy = Factory::instance().create<Enemy>("P");
                break;
            case 'a':
                enemy = Factory::instance().create<Enemy>("A");
                break;
            default:
                
                continue;
            }

            if (enemy)
                newSquad.addEnemy(std::move(enemy));
        }
    }

    m_enemies.push_back(std::move(newSquad));
}
