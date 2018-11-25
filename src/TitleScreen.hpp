#ifndef TITLESCREEN_HPP
#define TITLESCREEN_HPP

#include "Screen.hpp"

class TitleScreen : public Screen
{
    public:
        explicit TitleScreen(sf::RenderWindow& window);
        std::unique_ptr<Screen> execute() override;
        
        bool spawnTitle();
        bool paralax();
        bool fade();
    
    private:
        sf::Sprite bg, bed, win;
        sf::Text title;
        sf::Texture bg_t, bed_t, win_t;
        sf::Font font;
};


#endif // TITLESCREEN_HPP