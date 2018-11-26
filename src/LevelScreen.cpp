#include "LevelScreen.hpp"
#include "RessourceLoader.hpp"
#include "Bell.h"
#include "camera.hpp"
#include "constantes.hpp"
#include <numeric>
#include "Cinematique.hpp"
#include "DJ.hpp"


LevelScreen::LevelScreen(sf::RenderWindow& win, int levelNumber, std::string musicName, bool stopMusicAtBegin) :
    Screen{win},
    env{RessourceLoader::getPath("map/map" + std::to_string(levelNumber) + ".png")},
    maze{env},
    sortie(PORTE),
    sablier(SABLIER),
    player{&maze, &sortie, env.getMapLife()},
    musicName_{musicName},
    stopMusicAtBegin_{stopMusicAtBegin}
{
    lvl              = levelNumber;
    sf::Vector2i tot = std::accumulate(env.getDepart().begin(), env.getDepart().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos(tot.x, tot.y);
    pos /= static_cast<float>(env.getDepart().size());
    player.setInitialPosition(pos * static_cast<float>(PIXEL_SIZE) + sf::Vector2f(PIXEL_SIZE / 2, PIXEL_SIZE / 2));

    sf::Vector2i tot1 = std::accumulate(env.getArrivee().begin(), env.getArrivee().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos1(tot1.x, tot1.y);
    pos1 /= static_cast<float>(env.getArrivee().size());
    sortie.setPosition(pos1.x * PIXEL_SIZE, pos1.y * PIXEL_SIZE);

    chandeliers = Chandelier::createChandeliers("map/map" + std::to_string(levelNumber) + ".txt", PIXEL_SIZE);
    for(auto& c : chandeliers)
    {
        c.setMaze(&maze);
        c.setSortie(&sortie);
    }

    sf::Vector2i tot2 = std::accumulate(env.getDalles().begin(), env.getDalles().end(), sf::Vector2i(0, 0));
    sf::Vector2f pos2(tot2.x, tot2.y);
    pos2 /= static_cast<float>(env.getDalles().size());

    lucioles.emplace_back(&maze, &sortie);
    lucioles.back().set_coordd(pos2.x * PIXEL_SIZE, pos2.y * PIXEL_SIZE);
    lucioles.back().set_coordf(pos1.x * PIXEL_SIZE, pos1.y * PIXEL_SIZE);

    if(env.getBonus().size() != 0)
    {
        sf::Vector2i tot3 = std::accumulate(env.getBonus().begin(), env.getBonus().end(), sf::Vector2i(0, 0));
        sf::Vector2f pos3(tot3.x, tot3.y);
        pos3 /= static_cast<float>(env.getBonus().size());
        sablier.setPosition(pos3.x * PIXEL_SIZE, pos3.y * PIXEL_SIZE);
    }
    else
        sablier.kill();


    fond.setSize({2000, 2000});
    fond.setPosition(-400, -400);
    fond.setTexture(RessourceLoader::getTexture("sprites/fond_noir_9.png"));
    RessourceLoader::getTexture("sprites/fond_noir_9.png")->setRepeated(true);
}

std::unique_ptr<Screen> LevelScreen::execute()
{
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
            if(event.type == sf::Event::JoystickButtonPressed)
            {
                switch(event.joystickButton.button)
                {
                    case 0 :
                        player.ring([this]()
                        {
                            Bell::getInstance().add(&maze,
                                                    &sortie,
                                                    player.getPosition().x,
                                                    player.getPosition().y);
                            env.switchPillars();
                            maze.parseWall(env);
                        });

                        break;
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        player.ring([this]()
                        {
                            Bell::getInstance().add(&maze,
                                                    &sortie,
                                                    player.getPosition().x,
                                                    player.getPosition().y);
                            env.switchPillars();
                            maze.parseWall(env);
                        });

                        break;
                    case sf::Keyboard::L :
                        lucioles.emplace_back(&maze, &sortie);
                        lucioles.back().set_coordd(player.getPosition().x, player.getPosition().y);
                        lucioles.back().set_coordf(Utils::random(env.width * PIXEL_SIZE),
                                                   Utils::random(env.height * PIXEL_SIZE));
                        break;
                }
            }
        }

        globalClock::getClock().restart();


        player.movement(globalClock::getClock().frameTime(), env.getObstacles()); //Mouvement du personnage


        if(sortie.touchPlayer(player.getHitbox()))
        {
            Bell::getInstance().clear();
			if (lvl < 3) {
				return std::make_unique<LevelScreen>(window_, lvl+1, "lastinghope.ogg",false);
			}
			else if(lvl<9)
			{
				DJ::getInstance().stopAllMusic();
				return std::make_unique<Cinematique>(window_, RessourceLoader::getPath(std::to_string(lvl+1)), "cinematique.ogg", false, std::make_unique<LevelScreen>(window_, lvl+1, "lastinghope.ogg"));
			}
			else
			{
				return std::make_unique<Cinematique>(window_, RessourceLoader::getPath(std::to_string(lvl + 1)), "seeker.ogg", false, std::make_unique<LevelScreen>(window_, lvl + 1,"" ,false));
			}
			

			
        }

        if(sablier.touchPlayer(player.getHitbox()))
        {
			DJ::getInstance().playSound("sablier.wav");
            sablier.kill();
            player.setFullLife();
        }


        for(Chandelier& chand : chandeliers)
            chand.gestion(globalClock::getClock().frameTime());


        for(Luciole& lu : lucioles)
            lu.mouv();
        for(Chandelier& chand : chandeliers)
            chand.gestion(globalClock::getClock().frameTime());


        if(player.getLife() == 0)
        {
			Bell::getInstance().clear();

            sf::Text text;
            text.setFont(RessourceLoader::getFont("font/Dry Brush.ttf"));
            text.setString("Game Over");
            text.setCharacterSize(90);
            text.setPosition(WINDOW_SIZE_X / 2.0, 600);

            std::vector<sf::Text> v;
            v.push_back(text);

            return std::make_unique<Cinematique>(window_,
                                                 RessourceLoader::getPath("gameOver"),
                                                 v,
                                                 false,
                                                 std::make_unique<LevelScreen>(window_, lvl));
        }


        sf::View view = scrollCamera(env, player);
        view.setViewport(window_.getView().getViewport());
        window_.setView(view);
        
        window_.clear();
        window_.draw(fond);

        Bell::getInstance().draw(window_); // Draw visible walls

        env.drawPillars(window_);

        player.draw(window_);
        for(Chandelier& chand : chandeliers)
            chand.draw(window_);
        for(Luciole& lu : lucioles)
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

		sablier.update();
		sablier.draw(window_);

        window_.display();


        sf::sleep(sf::milliseconds(10));
    }
}
