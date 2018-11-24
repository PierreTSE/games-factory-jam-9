#include "Luciole.h"
#include<iostream>
#include <stdlib.h>
#include"globalClock.hpp"
#include<cmath>
#include "constantes.hpp"
#include "RessourceLoader.hpp"

using namespace std;


float Luciole::distance()
{
	double dx = solx - abs;
	double dy = soly - ord;
	return sqrt(dx*dx + dy * dy);
}

float Luciole::angle()
{
	//globalClock::globalClock().frameTime().asSeconds();
	return atan2(soly-ord,solx-abs);
}

#include <stdlib.h> 
long random_at_most(long max) {
	unsigned long
		num_bins = (unsigned long)max + 1,
		num_rand = (unsigned long)RAND_MAX + 1,
		bin_size = num_rand / num_bins,
		defect = num_rand % num_bins;
	long x;
	do {
		x = rand();
	} while (num_rand - defect <= (unsigned long)x);
	return x / bin_size;
}

void Luciole::mouv()
{
	double dir = angle();
	double tps = globalClock::getClock().frameTime().asSeconds();
	abs += vitesse * tps*cos(dir);
	ord += vitesse * tps*sin(dir);
}

void Luciole::draw(sf::RenderWindow & window)
{
	if (distance() > 1)
	{
		double dir = angle();
		double tps = globalClock::getClock().frameTime().asSeconds();
		abs += vitesse * tps*cos(dir);
		ord += vitesse * tps*sin(dir);

		lights.emplace_back(abs + 10, ord + 10);
		lights.back().setAlphaSpeed(600);
		lights.back().setAlpha(255);
		lights.back().setRadiusSpeed(0);
		lights.back().setRadius(50);
		lights.back().setDrawCircle(false);
	}



	for (size_t i = 0; i < lights.size(); i++)
		lights[i].update();

	lights.erase(std::remove_if(lights.begin(),
		lights.end(),
		[](auto& elem) { return elem.isDead(); }),
		lights.end());
	obj.setPosition(abs, ord);
	window.draw(obj);
	for (size_t i = 0; i < lights.size(); i++)
		lights[i].draw(window);

	sprite.setPosition(abs, ord);
	sprite.draw(window);
}

void Luciole::set_coordd(float X, float Y)
{
	abs = X;
	ord = Y;
}

void Luciole::set_coordf(float X, float Y)
{
	solx = X;
	soly = Y;
}




Luciole::Luciole() :
	sprite(FLAMING, AnimatedSprite(4, sf::milliseconds(200), RessourceLoader::getTexture("sprites/sprites_feufollet.png")))
{

	sprite.setScale(0.5, 0.5);
}