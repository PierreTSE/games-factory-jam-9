#include "Utils.h"



int Utils::random(int min, int max)
{
    std::random_device rd;
    static std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(eng);
}

int Utils::random(int max)
{
    return random(0, max);
}

void fit(sf::Sprite & s)
{
    const double ratio = std::max(s.getTexture()->getSize().x / static_cast<double>(WINDOW_SIZE_X), s.getTexture()->getSize().y / static_cast<double>(WINDOW_SIZE_Y));
    s.setScale(1.0/ratio, 1.0/ratio);
}
