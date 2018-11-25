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
#include "Bell.h"

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

	Environment environment;
	environment.load(RessourceLoader::getPath("map/map10.png"));

    Player monPerso;
    
    
    
    Chandelier chand({50, 50}, {150, 50});

	Maze maze(environment);

	Luciole luciole(&maze);
	luciole.set_coordd(100, 100);
	luciole.set_coordf(500, 500);

    //Création de la fenetre du jeux
    sf::RenderWindow window(sf::VideoMode(1200, 720),
                            "SUPER BIZUT",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));
    
    
    
    sf::Sprite testDegueu(RessourceLoader::getTexture("sprites/test.png"));
    testDegueu.setScale(15, 15);

    //Tant que l'on joue (fenetre ouverte)
    while(window.isOpen())
    {
        //Création d'un objet récupérant les événements (touche clavier et autre)
        sf::Event event{};


        //Boucle des évennements
        while(window.pollEvent(event))
        {
            //Evenement de fermeture de la fenetre : on ferme le jeux
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        monPerso.ring();
                        if(Bell::getInstance().checkReady(sf::seconds(1000)))
                            Bell::getInstance().add(&maze, monPerso.getPosition().x, monPerso.getPosition().y);
                        break;
					case sf::Keyboard::Return:
						environment.switchPillars();
						maze.parseWall(environment);
						break;
                }
            }
        }

        globalClock::getClock().restart();

        monPerso.movement(globalClock::getClock().frameTime(), environment.getObstacles()); //Mouvement du personnage

        window.clear();
        window.draw(testDegueu);

        

        //luciole.mouv();
        //luciole.draw(window);

		bell.getInstance().draw(window);

		monPerso.draw(window);

		//test chandelier
		chand.gestion(globalClock::getClock().frameTime());
		window.draw(chand.objet_);

        window.display();

        sf::sleep(sf::milliseconds(10));
    }


    return 0;
}
