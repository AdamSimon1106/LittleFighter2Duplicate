#pragma once
#include "Screens/WelcomeScreen.h"
#include "Screens/LoadingScreen.h"
#include "Screens/IScreen.h"
#include "UI/Button.h"
#include "UI/Background.h"
#include "Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <iostream>
#include <stdexcept>

WelcomeScreen::WelcomeScreen(sf::RenderWindow& window, GameManager& manager) : IScreen(window, manager)
{
	sf::Vector2f screenSize( static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Welcome_bg"));
    m_startButton = Button("Ready To Play?", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);
}

void WelcomeScreen::handleEvents(sf::Event& ev) {

    if (ev.type == sf::Event::MouseButtonPressed &&
        ev.mouseButton.button == sf::Mouse::Left) {
        auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);

        if (m_startButton.isClicked(mousePos)) {
            m_manager.switchScreen(std::make_unique<LoadingScreen>(m_window, m_manager));
        }
    }
}
void WelcomeScreen::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
}