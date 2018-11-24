#ifndef LUCIOLE_H
#define LUCIOLE_H

#include <SFML/Graphics.hpp>

class Luciole
{
private:
	float abs ;
	float ord ;
	float solx;
	float soly;
	float vitesse = 100;
	sf::RectangleShape obj;
public:
	Luciole();
	float distance();
	float angle();
	void mouv();
	void draw(sf::RenderWindow&window);
	void set_coordd(float X, float Y);
	void set_coordf(float X,float Y);
};

#endif