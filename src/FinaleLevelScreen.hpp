#ifndef FINALELEVELSCREEN_HPP
#define FINALELEVELSCREEN_HPP

#include "Screen.hpp"
#include "environment/Environment.hpp"
#include "Maze.h"
#include "Item.h"
#include "Character.h"


class FinaleLevelScreen : public Screen
{
    public:
        FinaleLevelScreen(sf::RenderWindow& win);
        std::unique_ptr<Screen> execute() override;

    private:
        Environment env;
        Maze maze;
        Item sortie;
        Player player;
        int lvl;
};


#endif // FINALELEVELSCREEN_HPP