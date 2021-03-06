#include "TitleScreen.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "constantes.hpp"
#include "LevelScreen.hpp"
#include "Utils.h"
#include "Cinematique.hpp"
#include "DJ.hpp"

TitleScreen::TitleScreen(sf::RenderWindow& window, const std::string& musicName, bool stopMusicAtBegin) : Screen{window}, musicName_{musicName}, stopMusicAtBegin_{stopMusicAtBegin}
{}


std::unique_ptr<Screen> TitleScreen::execute()
{
    title.setFont(RessourceLoader::getFont("font/Dry Brush.ttf"));
    title.setString("Bell me your Dreams");
    title.setCharacterSize(90);
    
    bg_t.loadFromFile(RessourceLoader::getPath("titlescreen/ecran_titre_fond.png"));
    bed_t.loadFromFile(RessourceLoader::getPath("titlescreen/ecran_titre_lit.png"));
    win_t.loadFromFile(RessourceLoader::getPath("titlescreen/ecran_titre_fenetre.png"));
    
    if(stopMusicAtBegin_)
        DJ::getInstance().stopAllMusic();

	if (!musicName_.empty())
		DJ::getInstance().playMusic(musicName_);

    
    bg.setTexture(bg_t);
    bed.setTexture(bed_t);
    win.setTexture(win_t);

    auto test = bg.getLocalBounds();
    
    centerOrigin(bg);
    bg.setPosition(WINDOW_SIZE_X/2.0, WINDOW_SIZE_Y/2.0);
    centerOrigin(bed);
    bed.setPosition(WINDOW_SIZE_X/2.0, WINDOW_SIZE_Y/2.0);
    centerOrigin(win);
    win.setPosition(WINDOW_SIZE_X/2.0, WINDOW_SIZE_Y/2.0);
    
    fit(bg);
    fit(bed);
    fit(win);
    
    centerOrigin(title);
    title.setPosition(WINDOW_SIZE_X/2.0, 600);
    
    bool continu;
    continu = spawnTitle();
    if(!continu)
        return std::unique_ptr<Screen>(nullptr);
    continu = paralax();
    if(!continu)
        return std::unique_ptr<Screen>(nullptr);
    continu = fade();
    if(!continu)
        return std::unique_ptr<Screen>(nullptr);
    return std::make_unique<LevelScreen>(window_, 1, "lastinghope.ogg", true);
}

bool TitleScreen::spawnTitle()
{
    sf::Time time;
    
    
    while(window_.isOpen())
    {
        sf::Event event;
        while(window_.pollEvent(event))
        {
            auto result = gestionEvent(event);
            if(result)
                return false;
        }
        
      
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0,0))) && time > sf::seconds(3))
            return true;
        
        globalClock::getClock().restart();
        
        time += globalClock::getClock().frameTime();
        
        double progression = (time-sf::seconds(1)) / sf::seconds(2);
        progression = std::clamp(progression, 0.0, 1.0);
        
        title.setFillColor(sf::Color(255, 255, 255, progression*255));
        
        window_.clear();
        window_.draw(bg);
        window_.draw(bed);
        window_.draw(win);
        window_.draw(title);
        window_.display();
    }
}

bool TitleScreen::paralax()
{
    sf::Time time;
    
    auto bgFrom = bg.getScale();
    auto bedFrom = bed.getScale();
    auto winFrom = win.getScale();


    while(window_.isOpen() && time < sf::seconds(3))
    {
        sf::Event event;
        while(window_.pollEvent(event))
        {
            auto result = gestionEvent(event);
            if(result)
                return false;
        }

        globalClock::getClock().restart();

        time += globalClock::getClock().frameTime();

        double progression = time / sf::seconds(3);
        progression = std::clamp(progression, 0.0, 1.0);

        bg.setScale(bgFrom * (float)(1.0 + progression*0.5));
        bed.setScale(bedFrom * (float)(1.0 + progression*1));
        win.setScale(winFrom * (float)(1.0 + progression*1.5));
        win.setColor(sf::Color(255, 255, 255, std::clamp(2-3*progression, 0.0, 1.0)*255));
        title.setScale(sf::Vector2f(1,1) * (float)(1.0 + progression*2));
        title.setPosition(title.getPosition().x, 600 + progression*600);

        window_.clear();
        window_.draw(bg);
        window_.draw(bed);
        window_.draw(win);
        window_.draw(title);
        window_.display();
    }
    
    return true;
}

bool TitleScreen::fade()
{
    sf::Time time;

    while(window_.isOpen() && time < sf::seconds(1))
    {
        sf::Event event;
        while(window_.pollEvent(event))
        {
            auto result = gestionEvent(event);
            if(result)
                return false;
        }

        globalClock::getClock().restart();

        time += globalClock::getClock().frameTime();

        double progression = time / sf::seconds(1);
        progression = std::clamp(progression, 0.0, 1.0);

        bg.setColor(sf::Color(255, 255, 255, 255 * (1.0-progression)));
        bed.setColor(sf::Color(255, 255, 255, 255 * (1.0-progression)));

        window_.clear();
        window_.draw(bg);
        window_.draw(bed);
        window_.display();
    }
    
    return true;
}
