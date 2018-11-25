#include "AnimatedEntity.hpp"
#include "Character.h"
#include "Chandelier.h"
#include "constantes.hpp"
#include "environment/Environment.hpp"
#include "globalClock.hpp"
#include "Luciole.h"
#include "RessourceLoader.hpp"
#include "SoundWave.h"
#include "Maze.h"
#include "camera.hpp"
#include "Bell.h"
#include "Screen.hpp"
#include "LevelScreen.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cinematique.hpp"

namespace fs = std::filesystem;

void mainTestEnvironment()
{
    Environment environment;
    environment.load(RessourceLoader::getPath("map/map7.png"));

    const float window_x = 800.f, window_y = 700.f;


    sf::RenderWindow window(sf::VideoMode(window_x, window_y),
                            "Test Environment",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

    const float ratio = 10.f;

    const sf::RectangleShape background({window_x, window_y});

    auto      chandeliers = Chandelier::createChandeliers(RessourceLoader::getPath("map/map10.txt"), ratio);
    for(auto& e : chandeliers)
    {
        e.objet_.move(ratio, ratio);
        e.objet_.scale(ratio, ratio);
    }

    while(window.isOpen())
    {
        sf::Event event{};
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        environment.switchPillars();
                        break;
                }
            }
        }

        globalClock::getClock().restart();

        //std::cout << globalClock::getClock().frameTime().asMilliseconds() << std::endl;

        window.clear();

        window.draw(background);
        environment.drawObstacles(window, ratio);

        for(auto& e : chandeliers)
        {
            e.gestion(globalClock::getClock().frameTime());
            e.draw(window);
        }

        window.display();

       // sf::sleep(sf::milliseconds(10));
    }
}

void mainTestChandelier()
{
    const float window_x = 800.f, window_y = 700.f;

    sf::RenderWindow window(sf::VideoMode(window_x, window_y),
                            "Test Environment",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

    const float ratio = 10.f;

    sf::Texture text;
    text.loadFromFile(RessourceLoader::getPath("map/map7.png"));
    sf::Sprite map(text);
    map.scale(ratio, ratio);

    auto      chandeliers = Chandelier::createChandeliers(RessourceLoader::getPath("map/map10.txt"), ratio);
    for(auto& e : chandeliers)
    {
        e.objet_.move(ratio, ratio);
        e.objet_.scale(ratio, ratio);
    }

    while(window.isOpen())
    {
        globalClock::getClock().restart();

        //std::cout << globalClock::getClock().frameTime().asMilliseconds() << std::endl;

        window.clear();

        window.draw(map);

        for(auto& e : chandeliers)
        {
            e.gestion(globalClock::getClock().frameTime());
            e.draw(window);
        }

        window.display();

        sf::sleep(sf::milliseconds(10));
    }
}


int main()
{
    // mainTestEnvironment();

    // Création de la fenêtre du jeu
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "SUPER BIZUT",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));


    // cinématiques d'abord
    std::unique_ptr<Screen> screen(new Cinematique(window, RessourceLoader::getPath("flashback"), std::make_unique<LevelScreen>(window, 3)));
    
    // direct sur le jeu
    //std::unique_ptr<Screen> screen(std::make_unique<LevelScreen>(window,3));


    while(screen)
        screen = screen->execute();


    return 0;
}
