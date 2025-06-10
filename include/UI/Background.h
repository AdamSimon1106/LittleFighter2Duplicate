#pragma once
#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {
public:
	Background(sf::Vector2f screenSize, sf::Color color);
	Background(sf::Vector2f screenSize, sf::Texture& texture);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vector2f m_screenSize;
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	sf::RectangleShape m_rectangleShape ;
	bool m_useTexture; 
	void setPictureToCover();
};