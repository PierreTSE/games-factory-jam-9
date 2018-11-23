#ifndef GLOBALCLOCK_HPP
#define GLOBALCLOCK_HPP

#include <SFML/System/Clock.hpp>


class globalClock
{
    public:
        globalClock() = default;
        sf::Time restart() noexcept;
        sf::Time frameTime() const noexcept;
        void stop() noexcept;
        void start() noexcept;
        void changeSpeed(double speed) noexcept;
        sf::Time timeSinceStartup() const noexcept;
        
        static globalClock& getClock();
        

    private:
        sf::Clock clock;
        sf::Time frame = sf::Time::Zero;
        sf::Time global = sf::Time::Zero;
        double factor = 1;
        bool running = true;
};

static globalClock instance;

#endif // GLOBALCLOCK_HPP