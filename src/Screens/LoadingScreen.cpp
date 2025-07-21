#pragma once
#include "Screens/LoadingScreen.h"
#include "Management/LevelLoader.h"
#include "Screens/CharacterSelectScreen.h"
#include "Screens/IScreen.h"
#include <SFML/System.hpp>
#include "UI/Background.h"
#include "UI/Button.h"
#include "Management/GameManager.h"
#include "Management/ResourceManager.h"
#include <iostream>
#include <stdexcept>

LoadingScreen::LoadingScreen(sf::RenderWindow& window, GameManager& manager) : IScreen(window, manager),
																			   m_dataLoader(DataLoader("data/data.txt")),
																			m_levelsLoader(LevelLoader("levelsData/levels.txt", sf::Vector2f(m_window.getSize())))
{
	AnimationManager::loadAnimations();
	sf::Vector2f screenSize(static_cast <sf::Vector2f> (m_window.getSize()));
	m_backGround = Background(screenSize, ResourceManager::instance().getTexture("screen_backgrounds/Loading_bg"));
	m_startButton = Button("  to character\n select screen", sf::Vector2f(screenSize.x / 4, screenSize.y / 4), sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Color::Transparent, 30);

	if (m_font.getInfo().family.empty()) {
		if (!m_font.loadFromFile("C:/Windows/Fonts/arialbd.ttf")) {
			throw std::runtime_error("Font failed to load!");
		}
	}

	m_chienese.setString("Currently Loading file: ");
	m_currentlyLoading.setString("data.txt");
	m_chienese.setFont(m_font); // assuming m_font is already loaded
	m_chienese.setCharacterSize(50);
	m_chienese.setFillColor(sf::Color::White);

	m_currentlyLoading.setFont(m_font);
	m_currentlyLoading.setCharacterSize(40);
	m_currentlyLoading.setFillColor(sf::Color::White);

	auto windowSize = m_window.getSize();

	m_chienese.setPosition(
		windowSize.x - m_chienese.getGlobalBounds().width - 100, // 10px from right
		200 // 10px from top
	);

	m_currentlyLoading.setPosition(
		windowSize.x - m_chienese.getGlobalBounds().width - 100,
		m_chienese.getPosition().y + m_chienese.getGlobalBounds().height + 20
	);
	
}

void LoadingScreen::update(sf::Time deltaTime) {
	if (m_dataLoader.loadCharacterDat()) {
		m_currentlyLoading.setString(m_dataLoader.getCurrentlyLoadingFile());
	}
	else if (m_levelsLoader.loadNewLevel()) {
		m_currentlyLoading.setString(m_levelsLoader.getCurrentlyLoadingFile());
	}
	else {
		m_canSwitchScreen = true;
	}
}

void LoadingScreen::handleEvents(sf::Event& ev) {
	
if (ev.type == sf::Event::MouseButtonPressed && 
	ev.mouseButton.button == sf::Mouse::Button::Left && m_canSwitchScreen) {
		auto mousePos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
		if (m_startButton.isClicked(mousePos)) {
			m_manager.switchScreen(std::make_unique<CharacterSelectScreen>(m_window, m_manager));
		}
	}
}

void LoadingScreen::render() {

	m_backGround->draw(m_window, sf::RenderStates::Default);
	m_startButton.draw(m_window, sf::RenderStates::Default);
	m_window.draw(m_chienese);
	m_window.draw(m_currentlyLoading);
	sf::sleep(sf::milliseconds(250.f));
}