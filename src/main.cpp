#include "../include/Management/GameManager.h"
#include "Management/ResourceManager.h"
#include "../include/UI/Background.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>


int main()
{
    try {
        // הקוד הרגיל
        sf::RenderWindow window(sf::VideoMode(800, 600), "Little Fighter Level");
        window.setFramerateLimit(60); // אופציונלי, כדי להגביל FPS

        Level level("lvl1bg");

        std::string enemiesLine = "b1 h1";
        level.addSquad(enemiesLine);

        Player player(ResourceManager::instance().getTexture("davis_ani"), 600.f);
        // Clock למדידת זמן בין פריימים
        sf::Clock clock;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key code: " << event.key.code << "\n";

                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    player.handleInput(PRESS_LEFT);
                    break;
                case sf::Keyboard::Right:
                    player.handleInput(PRESS_RIGHT);
                    break;
                case sf::Keyboard::Up: // או Space לפי העדפה
                    player.handleInput(PRESS_JUMP);
                    break;
                case sf::Keyboard::Enter:
                    std::cout << "enter(main)\n";
                    
                    player.handleInput(PRESS_ATTACK);
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    player.handleInput(RELEASE_LEFT);
                    break;
                case sf::Keyboard::Right:
                    player.handleInput(RELEASE_RIGHT);
                    break;
                default:
                    break;
                }
            }

            // חישוב זמן שעבר מאז הפריים הקודם
            float dt = clock.restart().asSeconds();

            // עדכון מצב המשחק
            level.update(dt);
            
            /*player.handleInput(RELEASE_RIGHT);
            player.handleInput(PRESS_LEFT);*/
            // ציור
            window.clear();
            
            level.render(window);
            player.draw(window);
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cout << "FATAL: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
