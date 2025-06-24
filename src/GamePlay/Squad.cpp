#include "GamePlay/Squad.h"
#include "GamePlay/Enemy.h"

void Squad::render(sf::RenderWindow& window)
{
	for (const auto& enemy : m_squad)
	{
		enemy->draw(window);
	}
}

void Squad::update(/*float dt*/ const sf::Vector2f playarPos)
{
	for (const auto& enemy : m_squad)
	{
		enemy->update(playarPos);
	}
}

void Squad::addEnemy(std::unique_ptr<Enemy> enemy)
{
	m_squad.push_back(std::move(enemy));
}
