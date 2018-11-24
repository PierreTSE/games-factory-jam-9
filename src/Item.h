#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utils.h"

class Item
{
	private :
		float x_, y_;
		float angle_;
		int sens_;
		float hue_;
		float alpha_;
		sf::RectangleShape shape_;
	public:
		Item();
		void setPosition(float x, float y);
		void discover();
		bool isInCircle(sf::Vector2f center, float radius);
		void update(sf::Time elpasedTime);
		void draw(sf::RenderWindow &window);
};

#endif // !1
