#include "Character.h"
#include<iostream>
#include <cmath>
#include "constantes.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"


Player::Player() :
    sprite(IDLE_DOWN, AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_down.png"),
                                     sf::IntRect{340, 0, 340, 600}))
{
    sprite.setup(IDLE_UP,
                 AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_up.png"),
                                sf::IntRect{340, 0, 340, 600}));
    sprite.setup(IDLE_LEFT,
                 AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_left.png"),
                                sf::IntRect{340, 0, 340, 600}));
    sprite.setup(IDLE_RIGHT,
                 AnimatedSprite(1, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_right.png"),
                                sf::IntRect{340, 0, 340, 600}));

    sprite.setup(WALKING_DOWN,
                 AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_down.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_UP,
                 AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_up.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_LEFT,
                 AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_left.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(WALKING_RIGHT,
                 AnimatedSprite(4, sf::milliseconds(250), RessourceLoader::getTexture("sprites/walking_right.png"),
                                sf::IntRect{0, 0, 340, 600}));


    sprite.setup(RINGING_DOWN,
                 AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_down.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_UP,
                 AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_up.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_LEFT,
                 AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_left.png"),
                                sf::IntRect{0, 0, 340, 600}));
    sprite.setup(RINGING_RIGHT,
                 AnimatedSprite(2, sf::milliseconds(250), RessourceLoader::getTexture("sprites/ringing_right.png"),
                                sf::IntRect{0, 0, 340, 600}));


    hitbox_.width = 50;
    hitbox_.height = 50;

    sprite.setScale(0.5, 0.5);

    orientation = Orientation::DOWN;
    animation = Animation::IDLE;
}


void Player::movement(const sf::Time& elapsedTime, std::vector<std::vector<bool>> const& map)
{
    if(!canMove)
        return;
    
    sf::Vector2f nextPos = position_;

    if(sf::Keyboard::isKeyPressed(
        sf::Keyboard::Right) /*&& (position_.x + form_.getGlobalBounds().width) < WINDOW_SIZE_X*/)
    {
        setOrientation(Orientation::RIGHT);
        setAnimation(Animation::WALKING);
        nextPos.x += speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position_.x > 0)
    {
        setOrientation(Orientation::LEFT);
        setAnimation(Animation::WALKING);
        nextPos.x -= speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position_.y > 0)
    {
        setOrientation(Orientation::UP);
        setAnimation(Animation::WALKING);
        nextPos.y -= speed_ * elapsedTime.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(
        sf::Keyboard::Down) /*&& (position_.y + form_.getGlobalBounds().height) < WINDOW_SIZE_Y*/)
    {
        setOrientation(Orientation::DOWN);
        setAnimation(Animation::WALKING);
        nextPos.y += speed_ * elapsedTime.asSeconds();
    }
    else
    {
        setAnimation(Animation::IDLE);
    }
    
    if(collision(map, nextPos))
        position_ = nextPos;
    else 
        setAnimation(Animation::IDLE);

    sprite.setPosition(position_);
}


bool Player::collision(std::vector<std::vector<bool>> const& map, sf::Vector2f pos)
{
    double factor = 720.0/61;
    sf::Vector2f min = sf::Vector2f{hitbox_.left, hitbox_.top}; - getPosition() + pos;
    sf::Vector2f max = min + sf::Vector2f{hitbox_.width, hitbox_.height};
    
    for(int i = floor(min.x/factor); i <= floor(max.x/factor); i++) {
        for(int j = floor(min.y/factor); j <= floor(max.y/factor); j++)
            if(map[j][i])
                return false;
    }

    return true;
}

Player::States Player::combineStates(Orientation ori, Animation ani)
{
    return static_cast<States>(static_cast<int>(ori) + 4 * static_cast<int>(ani));
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

sf::Vector2f Player::getPosition()
{
	return position_ + sprite.getSize()/2.f;
}

void Player::setCanMove(bool b)
{
    canMove = b;
}

void Player::ring()
{
    if(!canRing)
        return;
    setAnimation(Animation::RINGING);
    setCanMove(false);
    canRing = false;
    globalClock::getClock().executeIn(sf::seconds(0.74), [&]()
    {
        setAnimation(Animation::IDLE);
        setCanMove(true);
    });
    globalClock::getClock().executeIn(sf::seconds(1), [&]()
    {
        canRing = true;
    });
}



