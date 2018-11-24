#include "Luciole.h"
#include<iostream>
#include <stdlib.h>
#include"globalClock.hpp"
#include<cmath>

using namespace std;

Luciole::Luciole()
{
	obj.setSize({ 20, 20 });
	obj.setFillColor(sf::Color::Green);
}

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

void Luciole::mouv()
{
	if(distance() > 1)
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
}

void Luciole::draw(sf::RenderWindow & window)
{
	obj.setPosition(abs, ord);
	window.draw(obj);
	for (size_t i = 0; i < lights.size(); i++)
		lights[i].draw(window);
	
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

