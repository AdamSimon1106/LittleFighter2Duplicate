#include "../include/Management/GameManager.h"
#include "../include/UI/Background.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "bgTest");
	sf::Texture bgTexture;
	
	try {
		bgTexture.loadFromFile("bg_welcome_state.png");
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}
	Background bg(sf::Vector2f(window.getSize()), bgTexture);
	while (window.isOpen()) {
		sf::Event event;
	
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//stat of code
		window.clear();
		bg.draw(window,sf::RenderStates::Default);
		window.display();
	}

	return EXIT_SUCCESS;
}
