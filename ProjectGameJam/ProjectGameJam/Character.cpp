#include "Character.h"
#include<iostream>

Player::Player()
{
	//Initialisation du rectangle représentant le joueur
	form_.setSize({ 200,250 });
	form_.setPosition(0, 160);
	form_.setFillColor(sf::Color::Blue);

	hitbox_.width = 50;
	hitbox_.height = 50;

	

}



void Player::movement(sf::RenderWindow& window, const sf::Time& elapsedTime)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (position_.x + form_.getGlobalBounds().width) < WINDOW_SIZE_X)
	{
		position_.x += speed_ * elapsedTime.asSeconds();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && position_.x > 0)
	{
		position_.x -= speed_ * elapsedTime.asSeconds();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && position_.y > 0)
	{
		position_.y -= speed_ * elapsedTime.asSeconds();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (position_.y + form_.getGlobalBounds().height) < WINDOW_SIZE_Y)
	{
		position_.y += speed_ * elapsedTime.asSeconds();
	}
	

}



bool Player::collision()
{
	hitbox_.left = position_.x + 10;
	hitbox_.top = position_.y + 10;

	return true;
}


void Player::drawRectangle(sf::RenderWindow& window)
{
	form_.setPosition(position_);
	window.draw(form_);
}





