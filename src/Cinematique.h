#ifndef CINEMATIQUE_H
#define CINEMATIQUE_H
#include "constantes.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>


class Cinematique
{
private:
    std::vector<sf::Sprite> images_;

    sf::Time temps_      = sf::Time::Zero;
    sf::Time degradTime_ = sf::Time::Zero;

    /**
     * temps d'affichage d'une image de la cinématique
     */
    sf::Time frameTime_ = sf::seconds(5);

    sf::RectangleShape rect_ = sf::RectangleShape({static_cast<float>(WINDOW_SIZE_X), static_cast<float>(WINDOW_SIZE_Y)});

    size_t currentImg_ = 0;
    bool   first_      = true;
    size_t count_      = 0;

public:
    Cinematique(std::filesystem::path dirPath);

    void fondu(sf::RenderWindow& window);

    void animation(sf::RenderWindow& window);
};
#endif // CINEMATIQUE_H
