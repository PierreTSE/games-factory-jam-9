#include "Cinematique.h"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include <filesystem>

std::filesystem::path strip_root(const std::filesystem::path& p)
{
    const std::filesystem::path& parent_path = p.parent_path();
    if(parent_path.empty() || parent_path.string() == "/")
        return std::filesystem::path();
    else
        return strip_root(parent_path) / p.filename();
}

Cinematique::Cinematique(std::filesystem::path dirPath)
{
    if(!is_directory(dirPath))
        throw std::runtime_error("Not a directory" + dirPath.u8string());

    for(auto& file : std::filesystem::directory_iterator(dirPath))
    {
        images_.emplace_back(RessourceLoader::getTexture(strip_root(file.path()).u8string()));
        images_.back().scale(WINDOW_SIZE_X / images_.back().getGlobalBounds().width,
                             WINDOW_SIZE_Y / images_.back().getGlobalBounds().height);
    }

    rect_.setFillColor(sf::Color(0, 0, 0, 0));
}

void Cinematique::animation(sf::RenderWindow& window)
{
    bool continuer = true;
    while(count_ < images_.size())
    {
        // Création d'un objet récupérant les événements (touche clavier et autre)
        sf::Event event{};

        temps_ += globalClock::getClock().frameTime();
        window.clear();
        window.draw(images_.at(currentImg_));

        // Boucle des événements
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Space :
                        temps_ = sf::seconds(frameTime_.asSeconds());
                        break;
                }
            }
        }

        globalClock::getClock().restart();

        if(temps_ >= sf::seconds(frameTime_.asSeconds())) { fondu(window); }

        window.display();
    }
}

void Cinematique::fondu(sf::RenderWindow& window)
{
    degradTime_ += globalClock::getClock().frameTime();
    if(degradTime_ < sf::seconds(2) && count_ + 1 < images_.size())
    {
        if(degradTime_ < sf::seconds(1))
        {
            rect_.setFillColor(sf::Color(0, 0, 0, 255 * (degradTime_.asMilliseconds() / 1000.0)));
        }
        else
        {
            if(first_ && currentImg_ + 1 < images_.size())
            {
                first_ = false;
                currentImg_ += 1;
            }
            rect_.setFillColor(sf::Color(0, 0, 0, 255 - 255 * ((degradTime_.asMilliseconds() - 1000.0) / 1000.0)));
        }
        window.draw(rect_);
    }
    else
    {
        first_ = true;
        count_ += 1;
        degradTime_ = sf::Time::Zero;
        temps_      = sf::Time::Zero;
    }
}
