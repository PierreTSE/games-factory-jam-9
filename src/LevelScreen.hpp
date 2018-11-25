#ifndef LEVELSCREEN_HPP
#define LEVELSCREEN_HPP

#include "Screen.hpp"
#include "environment/Environment.hpp"
#include "Character.h"
#include "Luciole.h"
#include "Item.h"
#include "Chandelier.h"


class LevelScreen : public Screen
{
    public:
        LevelScreen(sf::RenderWindow& win, int levelNumber);
        std::unique_ptr<Screen> execute() override;
    
    private:
        Environment env;
		sf::RectangleShape fond;
        std::vector<Luciole> lucioles;
        std::vector<Chandelier> chandeliers;
        Maze maze;
		Item sortie;
		Item sablier;
        Player player;
		int lvl;
};


#endif // LEVELSCREEN_HPP