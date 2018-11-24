#include "Character.h"
#include<iostream>
#include "constantes.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"


Player::Player() :
    sprite(IDLE_DOWN, AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_down.png"), sf::IntRect{340,0,340,600}))
{
    sprite.setup(IDLE_UP, AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_up.png"), sf::IntRect{340,0,340,600}));

    sprite.setup(WALKING_DOWN, AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_down.png"), sf::IntRect{0,0,340,600}));
    sprite.setup(WALKING_UP, AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_up.png"), sf::IntRect{0,0,340,600}));


    sprite.setup(RINGING_DOWN, AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_down.png"), sf::IntRect{0,0,340,600}));
    sprite.setup(RINGING_UP, AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_up.png"), sf::IntRect{0,0,340,600}));
    
    
	hitbox_.width = 50;
	hitbox_.height = 50;

	sprite.setScale(0.5, 0.5);

	orientation = Orientation::DOWN;
	animation = Animation::IDLE;
}



void Player::movement(sf::RenderWindow& window, const sf::Time& elapsedTime)
{
    if(!canMove)
        return;
    
    
    
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) /*&& (position_.x + form_.getGlobalBounds().width) < WINDOW_SIZE_X*/)
	{
        setOrientation(Orientation::RIGHT);
        setAnimation(Animation::WALKING);
		position_.x += speed_ * elapsedTime.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position_.x > 0)
	{
        setOrientation(Orientation::LEFT);
        setAnimation(Animation::WALKING);
		position_.x -= speed_ * elapsedTime.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position_.y > 0)
	{
        setOrientation(Orientation::UP);
        setAnimation(Animation::WALKING);
		position_.y -= speed_ * elapsedTime.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) /*&& (position_.y + form_.getGlobalBounds().height) < WINDOW_SIZE_Y*/)
	{
        setOrientation(Orientation::DOWN);
        setAnimation(Animation::WALKING);
		position_.y += speed_ * elapsedTime.asSeconds();
	}
	else
    {
	    setAnimation(Animation::IDLE);
    }
	
    sprite.setPosition(position_);
}



bool Player::collision()
{
	hitbox_.left = position_.x + 10;
	hitbox_.top = position_.y + 10;

	return true;
}

Player::States Player::combineStates(Orientation ori, Animation ani)
{
    return static_cast<States>(static_cast<int>(ori) + 4* static_cast<int>(ani));
}

void Player::draw(sf::RenderTarget& target)
{
    sprite.draw(target);
}

void Player::setOrientation(Orientation o)
{
    if(!canMove)
        return;
    orientation = o;
    sprite.setState(combineStates(orientation, animation));
}

void Player::setAnimation(Animation a)
{
    if(!canMove)
        return;
    animation = a;
    sprite.setState(combineStates(orientation, animation));
}

void Player::setCanMove(bool b)
{
    canMove = b;
}

void Player::ring()
{
    if(!canMove)
        return;
    setAnimation(Animation::RINGING);
    setCanMove(false);
    globalClock::getClock().executeIn(sf::seconds(0.74), [&](){
        setAnimation(Animation::IDLE);
        setCanMove(true);
    });
}




