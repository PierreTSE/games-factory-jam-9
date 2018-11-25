#ifndef LEVELSCREEN_HPP
#define LEVELSCREEN_HPP

#include "Screen.hpp"
#include "environment/Environment.hpp"
#include "Character.h"
#include "Luciole.h"
#include "Chandelier.h"


class LevelScreen : public Screen
{
    public:
        LevelScreen(sf::RenderWindow& win, int levelNumber);
        std::unique_ptr<Screen> execute() override;
    
    private:
        Environment env;
        std::vector<Luciole> lucioles;
        std::vector<Chandelier> chandeliers;
        Maze maze;
        Player player;
};


#endif // LEVELSCREEN_HPP