#pragma once
#include "Screens/IScreen.h"
#include "Screens/InGameScreen.h"
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/GameManager.h"
#include "Gameplay/Player.h"
#include "Management/ResourceManager.h"

#include <iostream>
#include <stdexcept>
#include <memory>


InGameScreen::InGameScreen(sf::RenderWindow& window, GameManager& manager, std::shared_ptr<PlayerData> p, std::vector<std::shared_ptr<Ally>> allies) : IScreen(window, manager),
																						   m_controller(window, ResourceManager::instance().getLevel(0),
																						   std::vector<std::shared_ptr<Player>>{std::make_shared<Player>(*p)},
																						   allies)
{}


void InGameScreen::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();

	m_controller.updateWorld(dt); 
    

}

void InGameScreen::handleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased )
	{
		m_controller.handleInput(ev);

	}
}

void InGameScreen::render() {


	m_controller.render();

}