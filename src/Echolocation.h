#ifndef ECHOLOCATION_H
#define ECHOLOCATION_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Item.h"
#include "Maze.h"


class Echolocation
{
	private:
		Maze *maze_;
		std::unique_ptr<sf::RenderTexture> layout_;
		float alpha_;
		bool dead_;
		Item *sortie_;

		void detectHorizontalBorder(sf::Vector2f center, float radius, float j, float border);
		void detectVerticalBorder(sf::Vector2f center, float radius, float i, float border);
	public:
		Echolocation(Maze *maze, Item *sortie);
		void detect(sf::Vector2f center, float radius);
		void drawLayout(sf::RenderWindow &window);
		void update(sf::Time elapsedTime);
		bool isDead();
};

#endif