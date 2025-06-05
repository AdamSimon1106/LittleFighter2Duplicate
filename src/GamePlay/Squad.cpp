#include "Squad.h"

void Squad::draw(sf::RenderWindow& window)
{
	for (const auto& enemy : m_squad)
	{
		enemy.draw(window);
	}
}

void Squad::update(float dt)
{
	for (const auto& enemy : m_squad)
	{
		enemy.update(window);
	}
}
