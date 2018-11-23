#include <SFML/Graphics.hpp>
#include <iostream>
#include "globalClock.hpp"
#include "animatedSprite.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Texture t;
    t.loadFromFile("/home/thomas/temp/Actor2.png");
    
    AnimatedSprite as(3, sf::milliseconds(250), t, sf::IntRect{0, 48*4, 48, 48});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        std::cout << globalClock::getClock().restart().asMicroseconds() << std::endl;
        as.update();
            
        window.clear();
        window.draw(shape);
        window.draw(as);
        window.display();
    }

    return 0;
}