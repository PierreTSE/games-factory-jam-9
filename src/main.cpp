//#include "Character.h"
#include <SFML/Graphics.hpp>
#include "AnimatedEntity.hpp"
#include "globalClock.hpp"


enum characterState { WALKING_UP, WALKING_DOWN, WALKING_LEFT, WALKING_RIGHT };



int main()
{
	//Player monPerso;

	sf::Texture tex;
	tex.loadFromFile("/home/thomas/temp/Actor2.png");
    AnimatedSprite down(4, sf::milliseconds(250), tex, sf::IntRect{0, 48*4, 48, 48});
    AnimatedSprite left(4, sf::milliseconds(250), tex, sf::IntRect{0, 48*5, 48, 48});
    AnimatedSprite right(4, sf::milliseconds(250), tex, sf::IntRect{0, 48*6, 48, 48});
    AnimatedSprite up(4, sf::milliseconds(250), tex, sf::IntRect{0, 48*7, 48, 48});
    AnimatedEntity<characterState> redGuy(WALKING_DOWN, down);
    redGuy.setup(WALKING_LEFT, left);
    redGuy.setup(WALKING_RIGHT, right);
    redGuy.setup(WALKING_UP, up);

	//Création de la fenetre du jeux
	sf::RenderWindow window(sf::VideoMode(800, 600), "SUPER BIZUT", sf::Style::Default, sf::ContextSettings(0, 0, 8));

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
			if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up:
                        redGuy.setState(WALKING_UP);
                        break;
                    case sf::Keyboard::Down:
                        redGuy.setState(WALKING_DOWN);
                        break;
                    case sf::Keyboard::Right:
                        redGuy.setState(WALKING_RIGHT);
                        break;
                    case sf::Keyboard::Left:
                        redGuy.setState(WALKING_LEFT);
                        break;
                }
			}
		}
		
		globalClock::getClock().restart();
		


		window.clear();

		//monPerso.drawRectangle(window);
		//monPerso.movement(window, elapsedTime);//Mouvement du personnage
        redGuy.draw(window);

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