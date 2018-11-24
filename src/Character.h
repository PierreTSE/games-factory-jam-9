#ifndef CHARACTER_H
#define CHARACTER_H


#include <SFML/Graphics.hpp>

//Taille max de la fenetre de rendu en x
static constexpr unsigned int WINDOW_SIZE_X = 800;

//Taille max de la fenetre de rendu en y
static constexpr unsigned int WINDOW_SIZE_Y = 600;



class Player
{
protected:
	int speed_ = 300;
	sf::Vector2f position_ = { 0, 0 };
	sf::RectangleShape form_;
	sf::FloatRect hitbox_;

public:
	Player();
	void drawRectangle(sf::RenderWindow& window);
	bool collision();
	void movement(sf::RenderWindow &window, const sf::Time& elapsedTime);
	
};













#endif // !CHARACTER_H