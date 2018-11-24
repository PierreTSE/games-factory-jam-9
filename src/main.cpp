#include <SFML/Graphics.hpp>
#include <vector>

#include "Character.h"
#include "AnimatedEntity.hpp"
#include "globalClock.hpp"
#include "RessourceLoader.hpp"
#include"Luciole.h"
#include"constantes.hpp"
#include "Chandelier.h"
#include "SoundWave.h"


int main()
{
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
	luciole.set_coordd(500, 500);
	luciole.set_coordf(100, 100);

	std::vector<SoundWave> waves;

    //Création de la fenetre du jeux
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SUPER BIZUT", sf::Style::Default,
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
                    case sf::Keyboard::Space:
                        monPerso.ring();
						if((waves.size() == 0 || waves.back().getTime() > sf::milliseconds(500)))
							waves.emplace_back(monPerso.getPosition().x, monPerso.getPosition().y);
                        break;
                }
            }
        }

        globalClock::getClock().restart();


        monPerso.movement(window, globalClock::getClock().frameTime());//Mouvement du personnage

        window.clear();

		monPerso.draw(window);

		luciole.mouv();
		luciole.draw(window);

		for (size_t i = 0; i < waves.size(); i++)
		{
			waves[i].update();
			waves[i].draw(window);
		}

		waves.erase(std::remove_if(waves.begin(),
			waves.end(),
			[](auto& elem) { return elem.isDead(); }),
			waves.end());
		//test chandelier
		chand.gestion(elapsedTime);
		window.draw(chand.objet);

		window.display();

		sf::sleep(sf::milliseconds(10));

	}


    return 0;
}


