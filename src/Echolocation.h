#ifndef ECHOLOCATION_H
#define ECHOLOCATION_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utils.h"
#include "Item.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Echolocation
{
	private:
		sf::FloatRect obstacle_;
		std::unique_ptr<sf::RenderTexture> layout_;
		float alpha_;
		bool dead_;
		Item sortie;

		void detectHorizontalBorder(sf::Vector2f center, float raduis, float border);
		void detectVerticalBorder(sf::Vector2f center, float raduis, float border);
	public:
		Echolocation();
		void detect(sf::Vector2f center, float radius);
		void drawObstacle(sf::RenderWindow &window);
		void drawLayout(sf::RenderWindow &window);
		void update(sf::Time elpasedTime);
		bool isDead();
};

#endif