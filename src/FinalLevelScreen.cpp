#include "FinalLevelScreen.hpp"
#include "constantes.hpp"
#include "Bell.h"
#include "camera.hpp"
#include "Cinematique.hpp"
#include <numeric>
#include "Item.h"
#include "TitleScreen.hpp"
#include "DJ.hpp"


FinalLevelScreen::FinalLevelScreen(sf::RenderWindow& win, std::string musicName, bool stopMusicAtBegin):
    Screen{win},
    env{RessourceLoader::getPath("map/map11.png")},
    maze{env},
    sortie(PORTE),
    player{&maze, &sortie, env.getMapLife()},
    musicName_{musicName},
    stopMusicAtBegin_{stopMusicAtBegin}
{
    sf::Vector2i tot = std::accumulate(env.getDepart().begin(), env.getDepart().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos(tot.x, tot.y);
    pos /= static_cast<float>(env.getDepart().size());
    player.setInitialPosition(pos * static_cast<float>(PIXEL_SIZE) + sf::Vector2f(PIXEL_SIZE / 2, PIXEL_SIZE / 2));

    sf::Vector2i tot1 = std::accumulate(env.getArrivee().begin(), env.getArrivee().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos1(tot1.x, tot1.y);
    pos1 /= static_cast<float>(env.getArrivee().size());
    sortie.setPosition(pos1.x * PIXEL_SIZE, pos1.y * PIXEL_SIZE);
}


std::unique_ptr<Screen> FinalLevelScreen::execute()
{
    Bell::getInstance().add(&maze, &sortie, player.getPosition().x, player.getPosition().y, 0, 255, 600, 0);

    if(stopMusicAtBegin_)
        DJ::getInstance().stopAllMusic();

    if(!musicName_.empty())
        DJ::getInstance().playMusic(musicName_);
    
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
        }

        globalClock::getClock().restart();


        player.movement(globalClock::getClock().frameTime(), env.getObstacles()); //Mouvement du personnage

        if(sortie.touchPlayer(player.getHitbox()))
        {
            Bell::getInstance().clear();
            return std::make_unique<Cinematique>(window_, RessourceLoader::getPath("12"), true, 
                        std::make_unique<Cinematique>(window_, RessourceLoader::getPath("credit"), true, std::make_unique<TitleScreen>(window_)));
        }



        if(player.getLife() == 0)
            return std::make_unique<Cinematique>(window_, RessourceLoader::getPath("gameOver"), std::unique_ptr<Screen>(
                nullptr));

        sf::View view = scrollCamera(env, player);

        window_.setView(view);
        window_.clear();
        Bell::getInstance().draw(window_); // Draw visible walls

        player.draw(window_);

        sortie.update();
        sortie.draw(window_);
        
        

        window_.display();


        sf::sleep(sf::milliseconds(10));
    }
}