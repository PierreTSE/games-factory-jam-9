#ifndef LUCIOLE_H
#define LUCIOLE_H

#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "SoundWave.h"

class Luciole
{
private:
	float abs ;
	float ord ;
	float solx;
	float soly;
	float vitesse = 100;
	int temps = 0;
	enum States {
		FLAMING
	};
	AnimatedEntity<States> sprite;
	sf::RectangleShape obj;
	std::vector<SoundWave> lights;
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