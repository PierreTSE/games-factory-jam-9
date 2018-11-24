#include "Echolocation.h"

#include <iostream>

void Echolocation::detectHorizontalBorder(sf::Vector2f center, float radius, float border)
{
	if ((center.y - radius < border && center.y > border) ||
		(center.y + radius > border && center.y < border))
	{
		float largeur = abs(radius * cos(asin((center.y - border) / radius)));
		float x1 = center.x + largeur;
		float x2 = center.x - largeur;

		x1 = Utils::min(x1, obstacle_.left + obstacle_.width);
		x2 = Utils::max(x2, obstacle_.left);

		if (x1 - x2 > 0)
		{
			sf::RectangleShape line;
			line.setSize({ x1 - x2 + 5, 5 });
			line.setPosition(x2 - 2.5, border - 2.5);
			line.setFillColor(sf::Color::White);

			layout_.draw(line);
		}
	}
	
}

void Echolocation::detectVerticalBorder(sf::Vector2f center, float radius, float border)
{
	if ((center.x - radius < border && center.x > border) ||
		(center.x + radius > border && center.x < border))
	{
		float largeur = abs(radius * cos(asin((center.x - border) / radius)));
		float y1 = center.y + largeur;
		float y2 = center.y - largeur;

		y1 = Utils::min(y1, obstacle_.top + obstacle_.height);
		y2 = Utils::max(y2, obstacle_.top);

		if (y1 - y2 > 0)
		{
			sf::RectangleShape line;
			line.setSize({ 5, y1-y2 + 5});
			line.setPosition(border - 2.5, y2 - 2.5);
			line.setFillColor(sf::Color::White);

			layout_.draw(line);
		}
	}
}

Echolocation::Echolocation()
{
	obstacle_.left = 100;
	obstacle_.top = 100;
	obstacle_.width = 400;
	obstacle_.height = 200;

	alpha_ = 255;

	layout_.create(800, 600);
}

void Echolocation::detect(sf::Vector2f center, float radius)
{
	layout_.clear(sf::Color::Transparent);

	if (radius > 0)
	{
		detectHorizontalBorder(center, radius, obstacle_.top + obstacle_.height);
		detectHorizontalBorder(center, radius, obstacle_.top);

		detectVerticalBorder(center, radius, obstacle_.left + obstacle_.width);
		detectVerticalBorder(center, radius, obstacle_.left);

		alpha_ = 255;
	}
	
}

void Echolocation::drawObstacle(sf::RenderWindow & window)
{
	sf::RectangleShape obs;
	obs.setSize({ obstacle_.width, obstacle_.height });
	obs.setPosition(obstacle_.left, obstacle_.left);
	obs.setFillColor(sf::Color::Red);

	window.draw(obs);
}

void Echolocation::drawLayout(sf::RenderWindow & window)
{
	sf::Sprite render;
	render.setTexture(layout_.getTexture());
	render.setOrigin(400, 300);
	render.setPosition(400, 300);
	render.setScale(1, -1);
	render.setColor({ 255, 255, 255, (sf::Uint8)alpha_ });
	window.draw(render);
}

void Echolocation::update(sf::Time elpasedTime)
{
	alpha_ -= 100 * elpasedTime.asSeconds();
	if (alpha_ < 0)
		alpha_ = 0;
}
