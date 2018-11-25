#ifndef CINEMATIQUE_H
#define CINEMATIQUE_H
#include "constantes.hpp"

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Screen.hpp"


class Cinematique : public Screen
{
public:
    Cinematique(sf::RenderWindow& win, std::filesystem::path dirPath, std::unique_ptr<Screen> nextScreen = std::unique_ptr<Screen>());

    std::unique_ptr<Screen> execute() override;    

    void setFadeInTime(sf::Time fadeInTime) { fadeInTime_ = fadeInTime; }

    void setFadeOutTime(sf::Time fadeOutTime) {fadeOutTime_ = fadeOutTime; }

    void setFrameTime(sf::Time frameTime) { frameTime_ = frameTime; }

private:
    std::vector<sf::Sprite> images_;

    /**
     * temps du fondu en début d'image
     */
    sf::Time fadeInTime_ = sf::seconds(2);

    /**
     * temps du fondu en fin d'image
     */
    sf::Time fadeOutTime_ = sf::seconds(2);

    /**
     * temps d'affichage d'une image de la cinématique, avant le fondu
     */
    sf::Time frameTime_ = sf::seconds(5);

    sf::RectangleShape rect_ = sf::
            RectangleShape({static_cast<float>(WINDOW_SIZE_X), static_cast<float>(WINDOW_SIZE_Y)});

    void animation(sf::RenderWindow& window);

    std::unique_ptr<Screen> nextScreen_;
};
#endif // CINEMATIQUE_H
