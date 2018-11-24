#ifndef CHARACTER_H
#define CHARACTER_H


#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"


enum class Orientation {
    LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3
};

enum class Animation {
    IDLE = 0, WALKING = 1, RINGING = 2
};

class Player
{
    public:
        Player();
        bool collision(std::vector<std::vector<bool>> const& map);
        void movement(sf::RenderWindow& window, const sf::Time& elapsedTime);
        void draw(sf::RenderTarget& target);
        
        void setCanMove(bool b);
        
        void ring(); // Test
        
        void setOrientation(Orientation o);
        void setAnimation(Animation a);

		sf::Vector2f getPosition();
    
    private:
        enum States {
            IDLE_LEFT = 0, IDLE_UP = 1, IDLE_RIGHT = 2, IDLE_DOWN = 3,
            WALKING_LEFT = 4, WALKING_UP = 5, WALKING_RIGHT = 6, WALKING_DOWN = 7,
            RINGING_LEFT = 8, RINGING_UP = 9, RINGING_RIGHT = 10, RINGING_DOWN = 11
        };
        static States combineStates(Orientation ori, Animation ani);
    
        int speed_ = 300;
        sf::Vector2f position_ = {0, 0};
        AnimatedEntity<States> sprite;
        Orientation orientation;
        Animation animation;
        sf::FloatRect hitbox_;
        bool canMove = true;
        bool canRing = true;

};


#endif // !CHARACTER_H