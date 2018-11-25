#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Utils.h"
#include "AnimatedEntity.hpp"
#include "RessourceLoader.hpp"

class Item
{
	private :
		float x_, y_;
		float angle_;
		int sens_;
		float hue_;
		float alpha_;
		enum States {
			FLOATING
		};
		AnimatedEntity<States> sprite_;
	public:
		Item(float x, float y);
		void setPosition(float x, float y);
		void discover();
		bool isInCircle(sf::Vector2f center, float radius);
		bool touchPlayer(sf::FloatRect box);
		void update();
		void draw(sf::RenderWindow &window);
};

#endif // !1
