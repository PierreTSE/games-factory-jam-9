#include "Item.h"
#include "globalClock.hpp"

#include <iostream>

AnimatedEntity<Item::States> init(ItemType type) {
	if (type == PORTE)
		return AnimatedEntity<Item::States>(Item::States::FLOATING, AnimatedSprite(4, sf::milliseconds(200), RessourceLoader::getTexture("sprites/sprites_sortie.png")));
	else if (type == SABLIER)
		return AnimatedEntity<Item::States>(Item::States::FLOATING, AnimatedSprite(4, sf::milliseconds(200), RessourceLoader::getTexture("sprites/sprites_life.png")));
}
Item::Item(ItemType type) :

	type_{ type },
	sprite_(init(type))
{
	if (type == PORTE)
		alpha_ = 0;
	else if (type == SABLIER)
		alpha_ = 255;
	hue_ = 0;
	sens_ = 1;

	sprite_.setScale(0.8f, 0.8f);

	auto size = sprite_.getSize();
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
	if (dead_) return false;

	return box.contains(sf::Vector2f(x_, y_));
}

void Item::update()
{
	if (alpha_ > 0) {
		sf::Time elapsedTime = globalClock::getClock().frameTime();
		if (type_ == PORTE) hue_ += 100 * elapsedTime.asSeconds();

		if (type_ == PORTE) alpha_ -= 100 * elapsedTime.asSeconds();
		else alpha_ = 255;
	}
}

void Item::draw(sf::RenderWindow &window)
{
	if (!dead_)
	{
		if (alpha_ > 0)
		{
			sprite_.setPosition(x_ - 42, y_ - 48);
			if (type_ == PORTE) sprite_.setColor(Utils::makeHSV(hue_, 0.6f, 1.f, alpha_));
			sprite_.draw(window);
		}
	}	
}

void Item::kill()
{
	dead_ = true;
}
