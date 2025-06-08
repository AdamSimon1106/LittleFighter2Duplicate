#include "../include/States/InGameState.h"

InGameState::InGameState(sf::RenderWindow& window, GameManager& manager) : IState(window, manager),
																		   m_controller(Controller())
{}

void InGameState::update(sf::Time deltaTime)
{}

void InGameState::handleEvents(sf::Event& ev)
{}

void InGameState::render()
{
	sf::RectangleShape square;
	square.setSize(sf::Vector2f(m_window.getSize()));
	square.setFillColor(sf::Color::Blue);
	m_window.draw(square);
}
