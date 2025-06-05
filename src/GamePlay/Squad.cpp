#include "GamePlay/Squad.h"


void Squad::render(sf::RenderWindow& window)
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
		enemy.update(dt);
	}
}

void Squad::addEnemy(std::unique_ptr<Enemy> enemy)
{
	m_squad.push_back(std::move(enemy));
}
