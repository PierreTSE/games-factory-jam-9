#include <SFML/Graphics.hpp>
#include <vector>

#include "SoundWave.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Clock clock;

	std::vector<SoundWave> wave;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		
		if ((wave.size() == 0 || wave.back().getTime() > sf::milliseconds(500)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i position = sf::Mouse::getPosition(window);
			wave.emplace_back(position.x, position.y);
		}

		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		

        window.clear();
		
		for (size_t i = 0; i < wave.size(); i++)
		{
			wave[i].update(elapsed);
			wave[i].draw(window);

		}

		wave.erase(std::remove_if(wave.begin(),
								  wave.end(),
								  [](auto& elem){ return elem.isDead(); }),
				   wave.end());

			window.display();
		
    }

    return 0;
}