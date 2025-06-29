#pragma once
#include "../include/States/IState.h"
#include "../include/States/InGameState.h"
#include "../include/UI/Background.h"
#include "../include/UI/Button.h"
#include "../include/Management/GameManager.h"
#include "Management/ResourceManager.h"
#include "Management/AnimationManager.h"
#include <iostream>
#include <stdexcept>
#include <memory>

InGameState::InGameState(sf::RenderWindow& window, GameManager& manager) : IState(window, manager),

																 m_level("lvl1bg", static_cast<sf::Vector2f> (window.getSize())),
																 //m_player(sf::Vector2f(50, 600), "davis_ani", 300.f),
																 m_controller(window, std::make_unique<Level>("lvl1bg", static_cast<sf::Vector2f>(window.getSize())),
																 std::vector<std::shared_ptr<Player>>{},
																 std::vector<std::shared_ptr<Ally>>{})
{
	AnimationManager::loadAnimations();

	std::cout << "InGameState created, m_manager ptr: " << &m_manager << std::endl;

	



}



void InGameState::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    //m_level.update(dt);
	//m_player.update(dt);
    //m_level.handleCollisionsWithPlayer(m_player);
	m_controller.updateWorld(dt); // for later. dont let it stay hard coded
    
   

    /*player.handleInput(RELEASE_RIGHT);
    player.handleInput(PRESS_LEFT);*/
    // ????

}

void InGameState::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased )
	{
		m_controller.handleInput(ev);
		//m_player.handleInput(ev);
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
	m_controller.render();
    //m_level.render(m_window);
	//m_player.draw(m_window);
    //m_window.display();
}