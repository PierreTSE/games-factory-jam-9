#include "Character.h"
#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "globalClock.hpp"
#include "RessourceLoader.hpp"
#include"Luciole.h"
#include"constantes.hpp"

enum characterState { WALKING_UP, WALKING_DOWN, WALKING_LEFT, WALKING_RIGHT };



int main()
{
	Luciole luciole;
	luciole.set_coordd(60, 100);
	luciole.set_coordf(600,500);
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
			}
		}
		
		globalClock::getClock().restart();
		

		monPerso.movement(window, globalClock::getClock().frameTime());//Mouvement du personnage

		window.clear();

		monPerso.draw(window);
		if (luciole.distance() > 20)
		{
			luciole.mouv();
		}
		luciole.draw(window);
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