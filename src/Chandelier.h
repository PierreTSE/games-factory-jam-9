#include <cmath>
#ifndef CHANDELIER_H
#define CHANDELIER_H
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "AnimatedEntity.hpp"
#include "Maze.h"


class Chandelier
{
private:
    sf::Vector2i debut_;
    sf::Vector2i fin_;

    bool sens_;
    
    bool colorDir;

    const float vitesse_ = 0.05;

    enum States {
        FLAMING
    };
    AnimatedEntity<States> sprite;
    Maze *maze_;
    sf::Time timer_;

public:

    //TODO devra être remplacé par un sf::Sprite
    sf::RectangleShape objet_;

    Chandelier(sf::Vector2i debut, sf::Vector2i fin);

    static std::vector<Chandelier> createChandeliers(std::filesystem::path path);
    static std::vector<Chandelier> createChandeliers(std::filesystem::path path, int ratio);
    
    void setMaze(Maze* m);

    void gestion(sf::Time elapsedTime);

    void draw(sf::RenderWindow& window);
};
#endif // CHANDELIER_H
