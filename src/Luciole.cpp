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
    return sqrt(dx * dx + dy * dy);
}

float Luciole::angle()
{
    //globalClock::globalClock().frameTime().asSeconds();
    return atan2(soly - ord, solx - abs);
}

void Luciole::mouv()
{
    double dir = angle();
    double tps = globalClock::getClock().frameTime().asSeconds();
    abs += vitesse * tps * cos(dir);
    ord += vitesse * tps * sin(dir);
}

void Luciole::draw(sf::RenderWindow& window)
{
    if(distance() > 20)
    {
        double dir = angle();
        sf::Time tps = globalClock::getClock().frameTime();
		timer_ += tps;

        abs += vitesse * tps.asSeconds() * cos(dir);
        ord += vitesse * tps.asSeconds() * sin(dir);


		color += sens * 256 * tps.asSeconds();
		if (color > 255)
		{
			color = 255;
			sens = -sens;
		}
		else if (color < 128)
		{
			sens = 1;
		}
			

		sprite.setColor(sf::Color(color, color, color));
		sprite.setPosition(abs, ord);

		if (color == 255)
		{
			Bell::getInstance().add(maze_, abs + sprite.getSize().x / 2, ord + sprite.getSize().y / 2, 0, 255, 100, 255);
			timer_ = sf::Time::Zero;
		}
	}
	else
	{
		alpha -= 255 * globalClock::getClock().frameTime().asSeconds();
		if (alpha < 0)
			alpha = 0;
		sprite.setColor({ 255, 255, 255, (sf::Uint8)alpha });
	}

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

bool Luciole::isDead()
{
	return alpha == 0;
}




Luciole::Luciole(Maze *maze) :
	sprite(FLAMING, AnimatedSprite(4, sf::milliseconds(200), RessourceLoader::getTexture("sprites/sprites_feufollet.png")))
{
	maze_ = maze;
	sprite.setScale(0.5, 0.5);
}