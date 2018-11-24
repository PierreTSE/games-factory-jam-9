#include "Luciole.h"
#include<iostream>
#include <stdlib.h>
#include"globalClock.hpp"
#include<cmath>

using namespace std;

Luciole a;

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
	double dir = angle();
	double tps = globalClock::getClock().frameTime().asSeconds();
	abs += vitesse * tps*cos(dir);
	ord += vitesse * tps*sin(dir);
}

void Luciole::draw(sf::RenderWindow & window)
{
	obj.setPosition(abs, ord);
	window.draw(obj);
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

