#ifndef LUCIOLE_H
#define LUCIOLE_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "Bell.h"
#include "Item.h"

class Luciole
{
private:
	Maze *maze_;
	Item *sortie_;
	sf::Time timer_;
	float abs ;
	float ord ;
	float solx;
	float soly;
	float vitesse = 200;
	int temps = 0;
	float alpha = 255;
	float color = 128;
	float sens = 1;
	bool triggered_ = false;
	enum States {
		FLAMING
	};
	AnimatedEntity<States> sprite;
	sf::RectangleShape obj;
public:
	Luciole(Maze *maze, Item *sortie);
	float distance();
	float angle();
	void mouv();
	void draw(sf::RenderWindow&window);
	void set_coordd(float X, float Y);
	void set_coordf(float X,float Y);
	bool isDead();
	void checkColision(sf::FloatRect box);
};

#endif