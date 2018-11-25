#include "Cinematique.h"
#include <iostream>

Cinematique::Cinematique()
{
	images.push_back(sf::Sprite(RessourceLoader::getTexture("flashback/flashback1.png")));
	images.push_back(sf::Sprite(RessourceLoader::getTexture("flashback/flashback1_2.png")));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	for (sf::Sprite &s : images)
	{
		s.scale(0.5, 0.5);
	}
}

void Cinematique::animation(sf::RenderWindow &window)
{
	temps += globalClock::getClock().frameTime();
	window.draw(images.at(currentImg));
	if (temps > sf::seconds(5) && count+1<images.size()) {
		degradTime += globalClock::getClock().frameTime();
		if (degradTime < sf::seconds(2)) {
			if (degradTime < sf::seconds(1))
			{
				rect.setFillColor(sf::Color(0, 0, 0, 255 * (degradTime.asMilliseconds() / 1000.0)));
			}
			else
			{
				if (first && currentImg+1<images.size()) {
					first = false;
					currentImg += 1;
				}
				rect.setFillColor(sf::Color(0, 0, 0,255 - 255 * ((degradTime.asMilliseconds()-1000.0) / 1000.0)));
				
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
	
}

