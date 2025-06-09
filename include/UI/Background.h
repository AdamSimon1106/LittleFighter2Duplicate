#pragma once
#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {
public:
	Background(sf::RenderTarget& target, sf::Color color);
	Background(sf::RenderTarget& target, sf::Texture& texture);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RenderWindow m_window;
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	sf::RectangleShape colorRect;
	bool useTexture; 
	void setPictureToCover(sf::Sprite& sprite, const sf::RenderWindow& window, const sf::Texture& texture);
};