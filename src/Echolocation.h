#ifndef ECHOLOCATION_H
#define ECHOLOCATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

#include "Utils.h"
#include "Item.h"
#include "Maze.h"
#include "Bell.h"


class Echolocation
{
	private:
		Maze *maze_;
		std::unique_ptr<sf::RenderTexture> layout_;
		float alpha_;
		bool dead_;
		bool triggered_;
		Item sortie;

		void detectHorizontalBorder(sf::Vector2f center, float raduis, float j, float border);
		void detectVerticalBorder(sf::Vector2f center, float raduis, float i, float border);
	public:
		Echolocation(Maze *maze);
		void detect(sf::Vector2f center, float radius);
		void drawLayout(sf::RenderWindow &window);
		void update(sf::Time elpasedTime);
		bool isDead();
};

#endif