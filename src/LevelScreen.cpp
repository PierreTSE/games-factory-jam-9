#include "LevelScreen.hpp"
#include "RessourceLoader.hpp"
#include "Bell.h"
#include "camera.hpp"


LevelScreen::LevelScreen(sf::RenderWindow& win, int levelNumber) :
    Screen{win},
    env{RessourceLoader::getPath("map/map"+std::to_string(levelNumber)+".png")},
    maze{env},
    player{&maze}
{

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

        window_.display();

        sf::sleep(sf::milliseconds(10));
    }
}
