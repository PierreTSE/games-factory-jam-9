#ifndef ECHOLOCATION_H
#define ECHOLOCATION_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utils.h"

class Echolocation
{
	private:
		sf::FloatRect obstacle_;
		sf::RenderTexture layout_;
		float alpha_;


		void detectHorizontalBorder(sf::Vector2f center, float raduis, float border);
		void detectVerticalBorder(sf::Vector2f center, float raduis, float border);
	public:
		Echolocation();
		void detect(sf::Vector2f center, float radius);
		void drawObstacle(sf::RenderWindow &window);
		void drawLayout(sf::RenderWindow &window);
		void update(sf::Time elpasedTime);
};

#endif