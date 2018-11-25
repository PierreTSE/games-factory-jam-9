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

namespace fs = std::filesystem;

void mainTestEnvironment()
{
    Environment environment;
    environment.load(RessourceLoader::getPath("map/map10.png"));

    const float window_x = 800.f, window_y = 700.f;

    sf::RenderWindow window(sf::VideoMode(window_x, window_y),
                            "Test Environment",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

    const float ratio = 10.f;

	const sf::RectangleShape background({window_x, window_y});

    auto chandeliers = Chandelier::createChandeliers(RessourceLoader::getPath("map/map10.txt"), ratio);
    for(auto& e : chandeliers)
    {
        e.objet_.move(ratio,ratio);
        e.objet_.scale(ratio,ratio);
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

        sf::sleep(sf::milliseconds(10));
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
    text.loadFromFile(RessourceLoader::getPath("map/map10.png"));
    sf::Sprite map(text);
    map.scale(ratio, ratio);

    auto chandeliers = Chandelier::createChandeliers(RessourceLoader::getPath("map/map10.txt"), ratio);
    for(auto& e : chandeliers)
    {
        e.objet_.move(ratio,ratio);
        e.objet_.scale(ratio,ratio);
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


    // Ce code peux servir à faire des changements automatiques sur les sprites, à garder
    //for(auto path : {"../../rc/sprites/ringing_left.png"})
    //{
    //    sf::Image img, img2;
    //    img.loadFromFile(path);
    //    img2.create(img.getSize().x, img.getSize().y, sf::Color::Transparent);
    //
    //    int n = img.getSize().x / 340;
    //
    //    for(int i = 0; i < n - 1; i++)
    //    {
    //        for(int j = 0; j < 340; j++)
    //        {
    //            for(int k = 0; k < 600; k++)
    //                img2.setPixel(i * 340 + j, k, img.getPixel((i + 1) * 340 + j, k));
    //        }
    //    }
    //    for(int j = 0; j < 340; j++)
    //    {
    //        for(int k = 0; k < 600; k++)
    //            img2.setPixel((n - 1) * 340 + j, k, img.getPixel(j, k));
    //    }
    //
    //    img2.saveToFile(path);
    //}

    //Création de la fenetre du jeux
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "SUPER BIZUT",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));
    
    std::unique_ptr<Screen> screen(new LevelScreen(window, 10));
    while(screen)
        screen = screen->execute();
    
   

    return 0;
}
