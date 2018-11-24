#include "Item.h"

Item::Item()
{
	angle_ = 45;
	alpha_ = 0;
	hue_ = 0;
	sens_ = 1;

	shape_.setSize({ 20, 20 });
	shape_.setOrigin(10, 10);
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

void Item::update(sf::Time elapsedTime)
{
	if (alpha_ > 0) {
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
		shape_.setRotation(angle_);
		shape_.setPosition(x_, y_);
		shape_.setFillColor(Utils::makeHSV(hue_, 0.6f, 1.f, alpha_));
		window.draw(shape_);
	}
	
}
