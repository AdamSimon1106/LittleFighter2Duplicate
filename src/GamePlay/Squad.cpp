#include "Squad.h"
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

void Squad::addEnemy(std::unique_ptr<Enemy> enemy)
{
	m_squad.push_back(std::move(enemy));
}
