#include "Gameplay/Hunter.h"
#include "Factory/Factory.h"
#include "management/ResourceManager.h"

Hunter::Hunter(const sf::Vector2f pos)
	:Enemy(pos, "hunter")
{
}

void Hunter::handleCollision()
{
}

bool Hunter::m_registered = Factory<Enemy>::registerIt("H", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Hunter>(pos);
    });
