#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>


class AnimatedSprite : public sf::Sprite
{
    public:
        AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex);
        AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex, sf::IntRect textRect);

        void update();
    
    private:
        sf::Texture texture;
        sf::IntRect frameSize;
        int numFrame;
        int n;
        sf::Time timeBetween;
        sf::Vector2i origin;
        sf::Time animationProgress;
};


#endif // ANIMATEDSPRITE_HPP