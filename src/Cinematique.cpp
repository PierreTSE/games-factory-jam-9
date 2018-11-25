#include "Cinematique.h"
#include <iostream>

Cinematique::Cinematique()
{
	images.push_back(sf::Sprite(RessourceLoader::getTexture("flashback/1.png")));
	images.push_back(sf::Sprite(RessourceLoader::getTexture("flashback/2.png")));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	for (sf::Sprite &s : images)
	{
		s.scale(WINDOW_SIZE_X/s.getGlobalBounds().width, WINDOW_SIZE_Y/s.getGlobalBounds().height);
	}
}


void Cinematique::animation(sf::RenderWindow &window)
{
	bool continuer = true;
	while (count < images.size())
	{
		//Création d'un objet récupérant les événements (touche clavier et autre)
		sf::Event event{};

		temps += globalClock::getClock().frameTime();
		window.clear();
		window.draw(images.at(currentImg));

		//Boucle des évennements
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					temps = sf::seconds(5);
					break;
				}
			}
		}

		globalClock::getClock().restart();
		if (temps > sf::seconds(5)) {
			fondu(window);
		}
		window.display();

	}
}
	
	void Cinematique::fondu(sf::RenderWindow &window)
	{
		degradTime += globalClock::getClock().frameTime();
		if (degradTime < sf::seconds(2) && count+1<images.size()) {
			if (degradTime < sf::seconds(1))
			{
				rect.setFillColor(sf::Color(0, 0, 0, 255 * (degradTime.asMilliseconds() / 1000.0)));
			}
			else
			{
				if (first && currentImg + 1 < images.size()) {
					first = false;
					currentImg += 1;
				}
				rect.setFillColor(sf::Color(0, 0, 0, 255 - 255 * ((degradTime.asMilliseconds() - 1000.0) / 1000.0)));

			}
			window.draw(rect);
		}
		else {
			first = true;
			count += 1;
			degradTime = sf::Time::Zero;
			temps = sf::Time::Zero;
		}
	}

