#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

struct Chandelier
{
public:
	//void move();
	void gestion(sf::Time elapsedTime);
	Chandelier(sf::Vector2i debut,sf::Vector2i fin);

	sf::Vector2i debut_;
	sf::Vector2i fin_;
	sf::RectangleShape objet;
	bool sens;
	float vitesse = 0.05;
};