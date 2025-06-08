#include "Gameplay/Hunter.h"
#include "Factory/Factory.h"
#include "management/ResourceManager.h"

Hunter::Hunter()
	:Enemy(ResourceManager::instance().getTexture("hunter"))
{
}

void Hunter::handleCollision()
{
}

bool Hunter::m_registered = Factory<Enemy>::registerIt("H", []() {
    return std::make_unique<Hunter>();
    });
