#include "Objects/Weapons/Knife.h"

Knife::Knife(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
	
	setAnimation(AnimationManager::getAnimation(getName(), getTexture()));
	
}

void Knife::playAttack()
{
	std::cout << "in Knife attack playattack\n";
}

bool Knife::m_registered = Factory<PickableObject>::registerIt("k", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Knife>(pos, name);
	});
