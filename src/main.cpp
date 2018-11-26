#include "Cinematique.hpp"
#include "constantes.hpp"
#include "LevelScreen.hpp"
#include "Screen.hpp"
#include "TitleScreen.hpp"
#include "FinalLevelScreen.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>


int main()
{
    // Création de la fenêtre du jeu
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "Bell me your dreams",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));

    sf::Image icone;

    icone.loadFromFile(RessourceLoader::getPath("sprites/logo_64.png"));
    window.setIcon(icone.getSize().x, icone.getSize().y, icone.getPixelsPtr());


    //title screen
    //std::unique_ptr<Screen> screen(new TitleScreen(window, "nightmusic.ogg"));

    // cinématiques d'abord
    //std::unique_ptr<Screen> screen(new Cinematique(window, RessourceLoader::getPath("4"), "cinematique.ogg", false, std::make_unique<LevelScreen>(window, 3)));

    // direct sur le jeu
    std::unique_ptr<Screen> screen(std::make_unique<LevelScreen>(window, 10, "lastinghope.ogg"));

    // final level
    //std::unique_ptr<Screen> screen(std::make_unique<FinalLevelScreen>(window, "seeker.ogg", true));

    while(screen)
        screen = screen->execute();


    return 0;
}
