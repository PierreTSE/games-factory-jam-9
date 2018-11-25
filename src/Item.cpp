#include "Item.h"
#include "globalClock.hpp"

#include <iostream>

Item::Item(float x, float y) :
	sprite_(FLOATING, AnimatedSprite(4, sf::milliseconds(200), RessourceLoader::getTexture("sprites/sprites_sortie.png")))
{
	alpha_ = 0;
	hue_ = 0;
	sens_ = 1;

	sprite_.setScale(0.8f, 0.8f);

	auto size = sprite_.getSize();
	
	x_ = x - 42;
	y_ = y - 48;
}

void Item::setPosition(float x, float y)
{
	x_ = x;
	y_ = y;
}

void Item::discover()
{
	alpha_ = 255;
}

bool Item::isInCircle(sf::Vector2f center, float radius)
{
	sf::Vector2f diff = center - sf::Vector2f(x_, y_);
	return sqrt(diff.x*diff.x + diff.y*diff.y) < radius;
}

bool Item::touchPlayer(sf::FloatRect box)
{
	return box.contains(sf::Vector2f(x_, y_));
}

void Item::update()
{
	if (alpha_ > 0) {
		sf::Time elapsedTime = globalClock::getClock().frameTime();
		hue_ += 100 * elapsedTime.asSeconds();
		alpha_ -= 100 * elapsedTime.asSeconds();
		angle_ += sens_ * 70 * elapsedTime.asSeconds();
		if (angle_ < 0 || angle_ > 90)
			sens_ = -sens_;
	}
}

void Item::draw(sf::RenderWindow &window)
{
	if (alpha_ > 0)
	{
		sprite_.setPosition(x_ - 42, y_ - 48);
		sprite_.setColor(Utils::makeHSV(hue_, 0.6f, 1.f, alpha_));
		sprite_.draw(window);
	}
	
}
