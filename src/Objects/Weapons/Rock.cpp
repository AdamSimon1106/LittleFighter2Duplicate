#include "Objects/Weapons/Rock.h"

Rock::Rock(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
    setAnimation(AnimationManager::getAnimation(getName(), getTexture()));
    sf::Vector2f offset(10.f, -60.f);
    m_offset = offset;
}

void Rock::playAttack()
{
    std::cout << "in Rock attack playattack\n";
    auto pos = getPosition();
    std::cout << pos.x << " " << pos.y << "\n";
    sf::Vector2f newPos = pos + sf::Vector2f(90, 90);
    setPosition(newPos);
}

bool Rock::m_registered = Factory<PickableObject>::registerIt("r", [](const sf::Vector2f& pos, const std::string& name) {
    return std::make_unique<Rock>(pos, name);
    });