#pragma once
#include "../include/States/IState.h"
#include "../include/States/CharacterSelectState.h"
#include "../include/States/InGameState.h"
#include "../include/UI/Background.h"
#include "../include/UI/Button.h"
#include "../include/Management/GameManager.h"
#include <iostream>
#include <stdexcept>

CharacterSelectState::CharacterSelectState(sf::RenderWindow& window, GameManager& manager) : IState(window, manager)
{
	if (!m_bgTexture.loadFromFile("resources/state_backgrounds/bg_cc.png")) throw std::runtime_error("From CharcterSelectState - bg image not found");

	sf::Vector2f screenSize(static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, m_bgTexture);
	m_startButton = Button("Start Game", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);

}

void CharacterSelectState::update(sf::Time deltaTime) {

}

void CharacterSelectState::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::MouseButtonPressed && 
		ev.mouseButton.button == sf::Mouse::Button::Left) {
		auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		if (m_startButton.isClicked(mousePos)) {
			m_manager.switchState(std::make_unique<InGameState>(m_window, m_manager));
		}
	}
}

void CharacterSelectState::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
}