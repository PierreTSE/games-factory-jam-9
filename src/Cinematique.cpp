#include "Cinematique.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include <iostream>

std::filesystem::path strip_root(const std::filesystem::path& p)
{
    const std::filesystem::path& parent_path = p.parent_path();
    if(parent_path.empty() || parent_path.string() == "/")
        return std::filesystem::path();
    else
        return strip_root(parent_path) / p.filename();
}

Cinematique::
Cinematique(sf::RenderWindow& win, std::filesystem::path dirPath, std::unique_ptr<Screen> nextScreen) : Screen{win},
                                                                                                        nextScreen_{
                                                                                                            std::
                                                                                                            move(nextScreen)
                                                                                                        }
{
    dirPath = dirPath.parent_path() / std::filesystem::path("cinematiques") / dirPath.filename();

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

std::unique_ptr<Screen> Cinematique::execute()
{
    animation(window_);
    return std::move(nextScreen_);
}

void Cinematique::animation(sf::RenderWindow& window)
{
    sf::Event event{};

    for(auto& image : images_)
    {
        sf::Time currentTime = sf::milliseconds(1);
        globalClock::getClock().restart();

        bool skippingAsked = false;
        bool skipped       = false;
        bool animateFrame  = true;
        while(animateFrame)
        {
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && currentTime <= fadeInTime_ + frameTime_ && !skippingAsked)
                {
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space :
                            skippingAsked = true;
                            break;
                    }
                }
            }

            if(skippingAsked && currentTime > fadeInTime_ && !skipped)
            {
                currentTime = fadeInTime_ + frameTime_;
                skipped     = true;
            }

            window.clear();
            window.draw(image);

            if(currentTime < fadeInTime_)
            {
                rect_.setFillColor(sf::Color(0, 0, 0, 255 * ((fadeInTime_ - currentTime) / fadeInTime_)));
                window.draw(rect_);
            }
            else if(currentTime >= fadeInTime_ + frameTime_)
            {
                rect_.setFillColor(sf::Color(0, 0, 0, 255 * ((currentTime - frameTime_ - fadeInTime_) / fadeOutTime_)));
                window.draw(rect_);
            }

            if(currentTime >= fadeInTime_ + frameTime_ + fadeOutTime_) { animateFrame = false; }


            currentTime += globalClock::getClock().restart();
            //std::cout << currentTime.asSeconds() << std::endl;

            window.display();
        }
    }
}
