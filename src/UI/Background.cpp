#pragma once
#include "../include/UI/Background.h"

Background::Background(sf::Vector2f screenSize, sf::Color color) : m_screenSize(screenSize),
																   m_useTexture(false)
{
	m_rectangleShape =  sf::RectangleShape(sf::Vector2f(screenSize));
	m_rectangleShape.setFillColor(color);
}

Background::Background(sf::Vector2f screenSize, sf::Texture& texture) : m_bgTexture(texture),
																		m_screenSize(screenSize),
																		m_useTexture(true)
{
	m_bgSprite.setTexture(m_bgTexture);
}

void Background::setPictureToCover()
{
	float scaleX = static_cast<float> (m_bgTexture.getSize().x) / m_screenSize.x;
	float scaleY = static_cast<float> (m_bgTexture.getSize().y) / m_screenSize.y;
	m_bgSprite.scale(scaleX, scaleY);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_bgSprite,states);
}

