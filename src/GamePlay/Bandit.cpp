#include "Gameplay/Bandit.h"
#include "Factory/Factory.h"
#include "management/ResourceManager.h"

Bandit::Bandit()
    :Enemy(ResourceManager::instance().getTexture("bandit"))
{

}

void Bandit::handleCollision()
{
}

bool Bandit::m_registered = Factory<Enemy>::registerIt("b", []() {
    return std::make_unique<Bandit>();
    });

