#include "AnimatedEntity.hpp"
#include "Character.h"
#include "constantes.hpp"
#include "environment/Environment.hpp"
#include "globalClock.hpp"
#include "Luciole.h"
#include "RessourceLoader.hpp"
#include "SoundWave.h"

#include <filesystem>
#include <vector>
#include <SFML/Graphics.hpp>


namespace fs = std::filesystem;

void mainTestEnvironment(fs::path rc)
{
    Environment environment;
    environment.load(rc / "map" / "map10.png");

    const float window_x = 800.f, window_y = 700.f;

    sf::RenderWindow window(sf::VideoMode(window_x, window_y),
                            "Test Environment",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

    const float ratio = 10.f;

	const sf::RectangleShape background({window_x, window_y});


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

        window.clear();

        window.draw(background);
        environment.drawObstacles(window, ratio);

        window.display();

        sf::sleep(sf::milliseconds(10));
    }

}


int main()
{
    const fs::path rc = "../rc";

    //mainTestEnvironment(rc);


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


    Player monPerso;

	Luciole luciole;
	luciole.set_coordd(100, 100);
	luciole.set_coordf(500, 500);

    std::vector<SoundWave> waves;

    //Création de la fenetre du jeux
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "SUPER BIZUT",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

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
                        if((waves.size() == 0 || waves.back().getTime() > sf::milliseconds(500)))
                            waves.emplace_back(monPerso.getPosition().x, monPerso.getPosition().y);
                        break;
                }
            }
        }

        globalClock::getClock().restart();


        monPerso.movement(window, globalClock::getClock().frameTime()); //Mouvement du personnage

        window.clear();

        monPerso.draw(window);

        luciole.mouv();
        luciole.draw(window);

        for(size_t i = 0 ; i < waves.size() ; i++)
        {
            waves[i].update();
            waves[i].draw(window);
        }

        waves.erase(std::remove_if(waves.begin(),
                                   waves.end(),
                                   [](auto& elem) { return elem.isDead(); }),
                    waves.end());

        window.display();

        sf::sleep(sf::milliseconds(10));
    }


    return 0;
}
