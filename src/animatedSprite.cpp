#include "animatedSprite.hpp"
#include "globalClock.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>


AnimatedSprite::AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex) :
    texture{tex},
    frameSize(0, 0, tex.getSize().x/nFrame, tex.getSize().y),
    numFrame{nFrame},
    n{0},
    timeBetween{time},
    origin{frameSize.left, frameSize.top},
    animationProgress{sf::Time::Zero}
{}

AnimatedSprite::AnimatedSprite(int nFrame, sf::Time time, const sf::Texture& tex, sf::IntRect textRect) :
    texture{tex},
    frameSize{textRect},
    numFrame{nFrame},
    n{0},
    timeBetween{time},
    origin{frameSize.left, frameSize.top},
    animationProgress{sf::Time::Zero}
{}

void AnimatedSprite::update()
{
    setTexture(texture, false);
    animationProgress += globalClock::getClock().frameTime();
    animationProgress %= timeBetween*(float)numFrame;
    int step = floor(animationProgress / timeBetween);
    frameSize.left = origin.x + step * frameSize.width;
    setTextureRect(frameSize);
}
