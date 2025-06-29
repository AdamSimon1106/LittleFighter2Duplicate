#include "../include/Management/GameManager.h"
#include "Management/ResourceManager.h"
#include "../include/UI/Background.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>


int main()
{
	try
	{
		GameManager gameManager;
		gameManager.run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown exception occurred." << std::endl;
		return EXIT_FAILURE;
	}
	

	


	
}
