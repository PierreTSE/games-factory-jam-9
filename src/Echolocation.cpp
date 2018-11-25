#include "Echolocation.h"
#include "constantes.hpp"
#include <iostream>
#include "Bell.h"


void Echolocation::detectHorizontalBorder(sf::Vector2f center, float radius, float j, float border)
{
	if ((center.y - radius < border && center.y > border) ||
		(center.y + radius > border && center.y < border))
	{
		float largeur = std::abs(radius * cos(asin((center.y - border) / radius)));
		float x1 = center.x + largeur;
		float x2 = center.x - largeur;

		x1 = Utils::min(x1, (j+1) * PIXEL_SIZE);
		x2 = Utils::max(x2, j*PIXEL_SIZE);

		if (x1 - x2 > 0)
		{
			sf::RectangleShape line;
			line.setSize({ x1 - x2 + 5, 5 });
			line.setPosition(x2 - 2.5, border - 2.5);
			line.setFillColor(sf::Color::White);

			layout_->draw(line);
		}
	}
	
}

void Echolocation::detectVerticalBorder(sf::Vector2f center, float radius, float i, float border)
{
	if ((center.x - radius < border && center.x > border) ||
		(center.x + radius > border && center.x < border))
	{
		float largeur = abs(radius * cos(asin((center.x - border) / radius)));
		float y1 = center.y + largeur;
		float y2 = center.y - largeur;

		y1 = Utils::min(y1, (i+1)*PIXEL_SIZE);
		y2 = Utils::max(y2, i*PIXEL_SIZE);

		if (y1 - y2 > 0)
		{
			sf::RectangleShape line;
			line.setSize({ 5, y1-y2 + 5});
			line.setPosition(border - 2.5, y2 - 2.5);
			line.setFillColor(sf::Color::White);

			layout_->draw(line);
		}
	}
}

Echolocation::Echolocation(Maze *maze, Item *sortie)
{
	alpha_ = 255;
	dead_ = false;

	layout_.reset(new sf::RenderTexture);
	layout_->create(maze->getWidth()*PIXEL_SIZE, maze->getHeight()*PIXEL_SIZE);

	sortie_ = sortie;
	maze_ = maze;
}

void Echolocation::detect(sf::Vector2f center, float radius)
{
	layout_->clear(sf::Color::Transparent);

	if (radius > 0)
	{
		for (size_t i = 0; i < maze_->getWidth(); i++)
		{
			for (size_t j = 0; j < maze_->getHeight(); j++)
			{
				if(maze_->getWall(i, j).bot)
					detectHorizontalBorder(center, radius, j, (i+1) * PIXEL_SIZE);
				if (maze_->getWall(i, j).top)
					detectHorizontalBorder(center, radius, j, i * PIXEL_SIZE);

				if (maze_->getWall(i, j).right)
					detectVerticalBorder(center, radius, i, (j+1) * PIXEL_SIZE);
				if (maze_->getWall(i, j).left)
					detectVerticalBorder(center, radius, i, j * PIXEL_SIZE);
			}
		}

		if (sortie_->isInCircle(center, radius)) {
			sortie_->discover();

			
		}
		alpha_ = 255;
	}
	
}

void Echolocation::drawLayout(sf::RenderWindow & window)
{
	sf::Sprite render;
	render.setTexture(layout_->getTexture());
	render.setOrigin(render.getGlobalBounds().width/2, render.getGlobalBounds().height / 2);
	render.setPosition(render.getGlobalBounds().width / 2, render.getGlobalBounds().height / 2);
	render.setScale(1, -1);
	render.setColor({ 255, 255, 255, (sf::Uint8)alpha_ });
	window.draw(render);
}

void Echolocation::update(sf::Time elapsedTime)
{
	alpha_ -= 100 * elapsedTime.asSeconds();
	if (alpha_ < 0) {
		alpha_ = 0;
		dead_ = true;
	}		
}

bool Echolocation::isDead()
{
	return dead_;
}
