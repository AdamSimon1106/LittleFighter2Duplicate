#pragma once
#include "../include/States/IState.h"
#include "../include/States/LoadingState.h"
#include "../include/States/CharacterSelectState.h"
#include "../include/UI/Background.h"
#include "../include/UI/Button.h"
#include "../include/Management/GameManager.h"
#include <iostream>
#include <stdexcept>

LoadingState::LoadingState(sf::RenderWindow& window, GameManager& manager) : IState(window, manager)
{
	if (!m_bgTexture.loadFromFile("resources/state_backgrounds/bg_loading_1.png")) throw std::runtime_error("From LoadingState - bg image not found");

	sf::Vector2f screenSize(static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, m_bgTexture);
	m_startButton = Button("to char select state", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);
	std::cout << "LoadingState created, m_manager ptr: " << &m_manager << std::endl;

}

void LoadingState::update(sf::Time deltaTime) {

}

void LoadingState::handleEvents(sf::Event& ev) {
	
if (ev.mouseButton.button == sf::Mouse::Button::Left) {
		auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		if (m_startButton.isClicked(mousePos)) {
			m_manager.switchState(std::make_unique<CharacterSelectState>(m_window, m_manager));
		}
	}
}

void LoadingState::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
}