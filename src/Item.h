#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "RessourceLoader.hpp"

enum ItemType {
	PORTE, SABLIER
};

class Item
{
	public:
		enum States {
			FLOATING
		};
		Item(ItemType type);
		void setPosition(float x, float y);
		void discover();
		bool isInCircle(sf::Vector2f center, float radius);
		bool touchPlayer(sf::FloatRect box);
		void update(bool forced = false);
		void draw(sf::RenderWindow &window);
		void kill();

	private :
		float x_, y_;
		float angle_;
		int sens_;
		float hue_;
		float alpha_;
		ItemType type_;
		bool dead_ = false;
		
		AnimatedEntity<States> sprite_;
	
};

#endif // !1
