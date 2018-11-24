#include "Chandelier.h"


void Chandelier::gestion(sf::Time elapsedTime)
{
	float pas = vitesse * elapsedTime.asMilliseconds();

	if (debut_.x!= fin_.x) {
		
		if (sens && (fin_.x > objet.getPosition().x || abs(objet.getPosition().x-fin_.x)<pas)) {
			objet.move({ pas,0 });
		}
		else if (!sens && (debut_.x < objet.getPosition().x || abs(objet.getPosition().x - debut_.x)<pas)) {
			objet.move({ -pas,0 });
		}
		else{
			sens = !sens;
			}
	}
	else{
		
		if (sens && (fin_.y > objet.getPosition().y || abs(objet.getPosition().y - fin_.x) < pas)) {
			objet.move({ 0,pas });
		}
		else if (!sens && (debut_.y < objet.getPosition().y || abs(objet.getPosition().y - debut_.y) < pas)) {
			objet.move({ 0,-pas });
		}
		else
		{
			sens = !sens;
			}
	}
}

Chandelier::Chandelier(sf::Vector2i debut, sf::Vector2i fin)
{
	debut_ = debut;
	fin_ = fin;
	objet = sf::RectangleShape({ 10, 10 });
	objet.setPosition({ (float)debut.x,(float)debut.y });
	objet.setFillColor(sf::Color::Yellow);
	sens = true;
}



