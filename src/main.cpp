#include "../include/Management/GameManager.h"
#include "../include/UI/Background.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>


int main()
{
	GameManager gameManager;
	gameManager.run();
	return EXIT_SUCCESS;
}
