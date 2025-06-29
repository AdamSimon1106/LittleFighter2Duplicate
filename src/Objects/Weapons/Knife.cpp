#include "Objects/Weapons/Knife.h"

Knife::Knife(const sf::Vector2f pos, const std::string& name)
	:Weapon(pos, name)
{
	setScale(1.1f);
	setAnimation(AnimationManager::getAnimation(getName(), getTexture()));
	
}

void Knife::playAttack()
{
	std::cout << "in Knife attack playattack\n";
}

void Knife::move(const sf::Vector2f goal)
{
	for (const auto& offset : m_offsets)
	{
		sf::Vector2f newPos = goal + offset;
		setPosition(newPos);
	}
}

bool Knife::m_registered = Factory<PickableObject>::registerIt("k", [](const sf::Vector2f& pos, const std::string& name) {
	return std::make_unique<Knife>(pos, name);
	});
