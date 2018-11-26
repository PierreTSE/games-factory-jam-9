#include "AnimatedEntity.hpp"
#include "Character.h"
#include "Chandelier.h"
#include "constantes.hpp"
#include "environment/Environment.hpp"
#include "globalClock.hpp"
#include "Luciole.h"
#include "RessourceLoader.hpp"
#include "SoundWave.h"
#include "Maze.h"
#include "camera.hpp"
#include "Bell.h"
#include "Screen.hpp"
#include "LevelScreen.hpp"
#include "TitleScreen.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cinematique.hpp"
#include "FinaleLevelScreen.hpp"

void testSon()
{
    sf::SoundBuffer sb;
    sb.loadFromFile(RessourceLoader::getPath("audio/cloche.wav"));

    sf::Sound sound(sb);
    sound.play();

    while(sound.getStatus() == sf::Sound::Status::Playing)
    {
        
    }

}


namespace fs = std::filesystem;
int main()
{
    //testSon();

    // mainTestEnvironment();

    // Création de la fenêtre du jeu
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "Bell me your dreams",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));


    //title screen
    //std::unique_ptr<Screen> screen(new TitleScreen(window));

    // cinématiques d'abord
    //std::unique_ptr<Screen> screen(new Cinematique(window, RessourceLoader::getPath("1"), "cinematique.ogg", false, std::make_unique<LevelScreen>(window, 3)));
    
    // direct sur le jeu
    std::unique_ptr<Screen> screen(std::make_unique<LevelScreen>(window,1));


    while(screen)
        screen = screen->execute();


    return 0;
}
