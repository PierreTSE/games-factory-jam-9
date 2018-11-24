#include "Character.h"
#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "globalClock.hpp"
#include "RessourceLoader.hpp"
#include "constantes.hpp"



int main()
{
    // Ce code peux servir à faire des changements automatiques sur les sprites, à garder
    //for(auto path : {"../../rc/sprites/ringing_down.png"}) {
    //	sf::Image img, img2;
    //	img.loadFromFile(path);
    //	img2.create(img.getSize().x, img.getSize().y, sf::Color::Transparent);
    //	
    //	int n = img.getSize().x/340;
    //	
    //	for(int i = 0; i < n-1; i++) {
    //		for(int j = 0; j < 340; j++) {
    //			for(int k = 0; k < 600; k++)
    //				img2.setPixel(i*340+j, k, img.getPixel((i+1)*340+j, k));
    //		}
    //	}
	//	for(int j = 0; j < 340; j++) {
	//		for(int k = 0; k < 600; k++)
	//			img2.setPixel((n-1)*340+j, k, img.getPixel(j, k));
	//	}
	//	
	//	img2.saveToFile(path);
    //}
    
    
    
    
  	Player monPerso;



	//Création de la fenetre du jeux
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SUPER BIZUT", sf::Style::Default, sf::ContextSettings(0, 0, 8));


	//Tant que l'on joue (fenetre ouverte)
	while (window.isOpen())
	{
		//Création d'un objet récupérant les événements (touche clavier et autre)
		sf::Event event{};




		//Boucle des évennements
		while (window.pollEvent(event))
		{
			//Evenement de fermeture de la fenetre : on ferme le jeux
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space:
                        monPerso.ring();
                        break;
                }
			}
		}
		
		globalClock::getClock().restart();


        monPerso.movement(window, globalClock::getClock().frameTime());//Mouvement du personnage

        
		window.clear();
        monPerso.draw(window);
		window.display();


		sf::sleep(sf::milliseconds(10));
		

	}

	

    return 0;
}



/*
sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	
	
*/





/*

Player monPerso;


	//Création de la fenetre du jeux
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SUPER BIZUT", sf::Style::Default, sf::ContextSettings(0, 0, 8));

	//Création de la clock
	sf::Clock clock;

	sf::Time timer = sf::Time::Zero;

	//Tant que l'on joue (fenetre ouverte)
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();

		timer += elapsedTime;


		//Création d'un objet récupérant les événements (touche clavier et autre)
		sf::Event event{};




		//Boucle des évennements
		while (window.pollEvent(event))
		{
			//Evenement de fermeture de la fenetre : on ferme le jeux
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();

		monPerso.drawRectangle(window);
		monPerso.movement(window, elapsedTime);//Mouvement du personnage



		window.display();


		sf::sleep(sf::milliseconds(10));
		
		*/