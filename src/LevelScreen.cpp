#include "LevelScreen.hpp"
#include "RessourceLoader.hpp"
#include "Bell.h"
#include "camera.hpp"
#include "constantes.hpp"
#include <numeric>


LevelScreen::LevelScreen(sf::RenderWindow& win, int levelNumber) :
    Screen{win},
    env{RessourceLoader::getPath("map/map"+std::to_string(levelNumber)+".png")},
    maze{env},
    player{&maze}
{
    sf::Vector2i tot = std::accumulate(env.getDepart().begin(), env.getDepart().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos(tot.x, tot.y);
    pos /= (float)env.getDepart().size();
    player.setInitialPosition(pos*(float)PIXEL_SIZE + sf::Vector2f(PIXEL_SIZE/2, PIXEL_SIZE/2));
}

std::unique_ptr<Screen> LevelScreen::execute()
{
    while(window_.isOpen())
    {
        //Création d'un objet récupérant les événements (touche clavier et autre)
        sf::Event event{};


        //Boucle des évennements
        while(window_.pollEvent(event))
        {
            auto result = gestionEvent(event);
            if(result)
                return std::move(*result);
            
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        player.ring([this]() {
                            Bell::getInstance().add(&maze, player.getPosition().x, player.getPosition().y);
                            env.switchPillars();
                            maze.parseWall(env);
                        });
                        
                        break;
					case sf::Keyboard::L:
						lucioles.emplace_back(&maze);
						lucioles.back().set_coordd(player.getPosition().x, player.getPosition().y);
						lucioles.back().set_coordf(Utils::random(env.width_ * PIXEL_SIZE), Utils::random(env.height_ * PIXEL_SIZE));
						break;
                }
            }
        }

        globalClock::getClock().restart();

        
        
        player.movement(globalClock::getClock().frameTime(), env.getObstacles()); //Mouvement du personnage


        sf::View view = scrollCamera(env, player);

        for(Luciole& lu : lucioles)
            lu.mouv();
        for(Chandelier& chand : chandeliers)
            chand.gestion(globalClock::getClock().frameTime());


        window_.setView(view);

        window_.clear();
        Bell::getInstance().draw(window_); // Draw visible walls

        player.draw(window_);
        for(Chandelier& chand : chandeliers)
            chand.draw(window_);
        for(Luciole& lu : lucioles)
            lu.draw(window_);

		lucioles.erase(std::remove_if(lucioles.begin(),
			lucioles.end(),
			[](auto& elem) { return elem.isDead(); }),
			lucioles.end());

        window_.display();

        sf::sleep(sf::milliseconds(10));
    }
}
