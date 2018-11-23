#include "globalClock.hpp"


sf::Time globalClock::restart() noexcept
{
    sf::Time elapsed = clock.restart();
    
    if(running)
    {
        frame = elapsed * (float)factor;
        global += frame;
    }
    else
    {
        frame = sf::Time::Zero;
    }
    
    return frameTime();
}

sf::Time globalClock::frameTime() const noexcept
{
    return frame;
}

void globalClock::stop() noexcept
{
    running = false;
}

void globalClock::start() noexcept
{
    running = true;
}

void globalClock::changeSpeed(double speed) noexcept
{
    factor = speed;
}

sf::Time globalClock::timeSinceStartup() const noexcept
{
    return global;
}

globalClock& globalClock::getClock()
{
    return instance;
}
