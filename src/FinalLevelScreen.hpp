#ifndef FINALELEVELSCREEN_HPP
#define FINALELEVELSCREEN_HPP

#include "Screen.hpp"
#include "environment/Environment.hpp"
#include "Maze.h"
#include "Item.h"
#include "Character.h"


class FinalLevelScreen : public Screen
{
    public:
        FinalLevelScreen(sf::RenderWindow& win, std::string musicName = "", bool stopMusicAtBegin = true);
        std::unique_ptr<Screen> execute() override;

    private:
        Environment env;
        Maze maze;
        Item sortie;
        Player player;
        int lvl;

        std::string musicName_;
        bool stopMusicAtBegin_;
};


#endif // FINALELEVELSCREEN_HPP