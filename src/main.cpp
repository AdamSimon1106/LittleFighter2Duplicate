#include "../include/Management/GameManager.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "bgTest");
	sf::Sprite bgSprite;
	sf::Texture bgTexture;
	sf::Image img;
	
	try {
		bgTexture.loadFromFile("bg_welcome_state.png");
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}
	bgSprite.setTexture(bgTexture);
	bgSprite.scale(sf::Vector2f(window.getSize()));
	while (window.isOpen()) {
		sf::Event event;
	
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//stat of code
		window.clear();
		window.draw(bgSprite);
		window.display();
	}

	return EXIT_SUCCESS;
}
