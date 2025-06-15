#pragma once
#include "../include/States/IState.h"
#include "../include/States/InGameState.h"
#include "../include/UI/Background.h"
#include "../include/UI/Button.h"
#include "../include/Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <iostream>
#include <stdexcept>

InGameState::InGameState(sf::RenderWindow& window, GameManager& manager) : IState(window, manager), 
																			m_level("lvl1bg"),
																			m_player(sf::Vector2f(50, 600), "davis_ani", 300.f)
{

	std::cout << "InGameState created, m_manager ptr: " << &m_manager << std::endl;

	std::string enemiesLine = "b1 h1";
	m_level.addSquad(enemiesLine);

	std::string objectLine = "r r r r r r";
	m_level.addPickableObjects(objectLine);

}

void InGameState::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    m_level.update(dt);
	m_player.update(dt);

    /*player.handleInput(RELEASE_RIGHT);
    player.handleInput(PRESS_LEFT);*/
    // ????

}

void InGameState::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased )
	{
		m_player.handleInput(ev);
		//if (ev.mouseButton.button == sf::Mouse::Button::Left) {
		//	auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		//	if (m_startButton.isClicked(mousePos)) {
		//		m_manager.switchState(std::make_unique<InGameState>(m_window, m_manager));
		//	}
		//}
	}
}

void InGameState::render() {

	//m_backGround->draw(m_window, sf::RenderStates::Default);
	//m_startButton.draw(m_window, sf::RenderStates::Default);
    //m_window.clear();
	
    m_level.render(m_window);
	m_player.draw(m_window);
    //m_window.display();
}