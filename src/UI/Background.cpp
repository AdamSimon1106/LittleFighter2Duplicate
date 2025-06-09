#include<iostream>
#include "../include/UI/Background.h"

Background::Background(sf::Vector2f screenSize, sf::Color color) : m_screenSize(screenSize),
																   m_useTexture(false)
{
	m_rectangleShape =  sf::RectangleShape(sf::Vector2f(screenSize));
	m_rectangleShape.setFillColor(color);
}

Background::Background(sf::Vector2f screenSize, sf::Texture& texture) : m_bgTexture(&texture),
																		m_screenSize(screenSize),
																		m_useTexture(true)
{
	m_bgSprite.setTexture(*m_bgTexture);
	setPictureToCover();
}

void Background::setPictureToCover()
{
	m_bgSprite.setPosition(0, 0);

	float textureWidth = static_cast<float>(m_bgTexture -> getSize().x);
	float textureHeight = static_cast<float>(m_bgTexture -> getSize().y);

	float scaleX = m_screenSize.x / textureWidth;
	float scaleY = m_screenSize.y / textureHeight;

	m_bgSprite.setScale(scaleX, scaleY);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::cout << "[Background] draw() called, useTexture: " << m_useTexture << std::endl;
	if (m_useTexture) {
		std::cout << "Sprite position: " << m_bgSprite.getPosition().x << ", " << m_bgSprite.getPosition().y << "\n";
		std::cout << "Sprite scale: " << m_bgSprite.getScale().x << ", " << m_bgSprite.getScale().y << "\n";
		target.draw(m_bgSprite, states);

	}
	else
		target.draw(m_rectangleShape, states);
}


