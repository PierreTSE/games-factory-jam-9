#include "constantes.hpp"
#include "LevelScreen.hpp"
#include "Screen.hpp"
#include "TitleScreen.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>



namespace fs = std::filesystem;
int main()
{
    // Création de la fenêtre du jeu
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
                            "Bell me your dreams",
                            sf::Style::Default,
                            sf::ContextSettings(0, 0, 8));


    //title screen
    std::unique_ptr<Screen> screen(new TitleScreen(window, "nightmusic.ogg"));

    // cinématiques d'abord
    //std::unique_ptr<Screen> screen(new Cinematique(window, RessourceLoader::getPath("4"), "cinematique.ogg", false, std::make_unique<LevelScreen>(window, 3)));
    
    // direct sur le jeu
    //std::unique_ptr<Screen> screen(std::make_unique<LevelScreen>(window, 10));


    while(screen)
        screen = screen->execute();


    return 0;
}
