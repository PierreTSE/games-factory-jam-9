#include <SFML/Graphics.hpp>
#include <vector>

#include "SoundWave.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Clock clock;

	SoundWave wave;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// get global mouse position
			sf::Vector2i position = sf::Mouse::getPosition(window);
			wave.setCenter(position.x, position.y);
		}

		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		

        window.clear();
		
		wave.update(elapsed);
		wave.draw(window);
        
        window.display();
    }

    return 0;
}