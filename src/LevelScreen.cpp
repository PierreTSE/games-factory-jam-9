#include "LevelScreen.hpp"
#include "RessourceLoader.hpp"
#include "Bell.h"
#include "camera.hpp"
#include "constantes.hpp"
#include <numeric>
#include "Cinematique.hpp"


LevelScreen::LevelScreen(sf::RenderWindow& win, int levelNumber) :
    Screen{win},
    env{RessourceLoader::getPath("map/map" + std::to_string(levelNumber) + ".png")},
    maze{env},
    sortie(0, 0),
    player{&maze, &sortie, env.getMapLife()}
{
    lvl = levelNumber;
    sf::Vector2i tot = std::accumulate(env.getDepart().begin(), env.getDepart().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos(tot.x, tot.y);
    pos /= (float) env.getDepart().size();
    player.setInitialPosition(pos * (float) PIXEL_SIZE + sf::Vector2f(PIXEL_SIZE / 2, PIXEL_SIZE / 2));

	sf::Vector2i tot1 = std::accumulate(env.getArrivee().begin(), env.getArrivee().end(), sf::Vector2i(0, 0));
	sf::Vector2f pos1(tot1.x, tot1.y);
	pos1 /= (float)env.getArrivee().size();
	sortie.setPosition(pos1.x * PIXEL_SIZE, pos1.y * PIXEL_SIZE);

    chandeliers = Chandelier::createChandeliers("map/map"+std::to_string(levelNumber)+".txt", PIXEL_SIZE);
	for (auto& c : chandeliers) {
		c.setMaze(&maze);
		c.setSortie(&sortie);
	}

	sf::Vector2i tot2 = std::accumulate(env.getDalles().begin(), env.getDalles().end(), sf::Vector2i(0, 0));
	sf::Vector2f pos2(tot2.x, tot2.y);
	pos2 /= (float)env.getDalles().size();

	lucioles.emplace_back(&maze, &sortie);
	lucioles.back().set_coordd(pos2.x * PIXEL_SIZE, pos2.y * PIXEL_SIZE);
	lucioles.back().set_coordf(pos1.x * PIXEL_SIZE, pos1.y * PIXEL_SIZE);
	
		
}

std::unique_ptr<Screen> LevelScreen::execute()
{
    while(window_.isOpen())
    {
        // Création d'un objet récupérant les événements (touche clavier et autre)
        sf::Event event{};

        //Boucle des événements
        while(window_.pollEvent(event))
        {
            auto result = gestionEvent(event);
            if(result)
                return std::move(*result);

            if(event.type == sf::Event::JoystickButtonPressed)
            {
                {
                    switch(event.joystickButton.button)
                    {
                        case 0:
                            player.ring([this]()
                                        {
                                            Bell::getInstance().add(&maze, &sortie, player.getPosition().x,
                                                                    player.getPosition().y);
                                            env.switchPillars();
                                            maze.parseWall(env);
                                        });

                            break;
                    }
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        player.ring([this]()
                                    {
                                        Bell::getInstance().add(&maze, &sortie, player.getPosition().x,
                                                                player.getPosition().y);
                                        env.switchPillars();
                                        maze.parseWall(env);
                                    });

                        break;
                }
            }
        }

        globalClock::getClock().restart();


        
        player.movement(globalClock::getClock().frameTime(), env.getObstacles()); //Mouvement du personnage
        if(sortie.touchPlayer(player.getHitbox()))
        {
            Bell::getInstance().clear();
            return std::unique_ptr<Screen>(new LevelScreen(window_, lvl + 1));
        }

        for(Chandelier& chand : chandeliers)
            chand.gestion(globalClock::getClock().frameTime());

        if(player.getLife() == 0)
            return std::make_unique<Cinematique>(window_, RessourceLoader::getPath("gameOver"));
        window_.clear();
        Bell::getInstance().draw(window_); // Draw visible walls
        player.draw(window_);
        for(Chandelier& chand : chandeliers)
            chand.draw(window_);
		for (Luciole& lu : lucioles)
		{
			lu.checkColision(player.getHitbox());
			lu.draw(window_);
		}

        lucioles.erase(std::remove_if(lucioles.begin(),
                                      lucioles.end(),
                                      [](auto& elem) { return elem.isDead(); }),
                       lucioles.end());
        sortie.update();
        sortie.draw(window_);

        sf::View view = scrollCamera(env, player);
        window_.setView(view);
        window_.display();


        sf::sleep(sf::milliseconds(10));
    }
}
