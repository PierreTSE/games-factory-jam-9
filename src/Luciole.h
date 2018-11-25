#ifndef LUCIOLE_H
#define LUCIOLE_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "Bell.h"

class Luciole
{
private:
	Maze *maze_;
	sf::Time timer_;
	float abs ;
	float ord ;
	float solx;
	float soly;
	float vitesse = 100;
	int temps = 0;
	float alpha = 255;
	float color = 128;
	float sens = 1;
	enum States {
		FLAMING
	};
	AnimatedEntity<States> sprite;
	sf::RectangleShape obj;
public:
	Luciole(Maze *maze);
	float distance();
	float angle();
	void mouv();
	void draw(sf::RenderWindow&window);
	void set_coordd(float X, float Y);
	void set_coordf(float X,float Y);
	bool isDead();
};

#endif