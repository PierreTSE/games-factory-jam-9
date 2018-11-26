#include "Cinematique.hpp"
#include "RessourceLoader.hpp"
#include "globalClock.hpp"
#include "Utils.h"
#include <iostream>
#include "DJ.hpp"

Cinematique::Cinematique(sf::RenderWindow& win, std::filesystem::path dirPath, std::unique_ptr<Screen> nextScreen) :
    Cinematique{win, dirPath, false, std::move(nextScreen)} {}

Cinematique::
Cinematique(sf::RenderWindow&       win,
            std::filesystem::path   dirPath,
            bool                    waitForSkip,
            std::unique_ptr<Screen> nextScreen) :
    Screen{win},
    waitForSkip_{waitForSkip},
    nextScreen_{std::move(nextScreen)}
{
    dirPath = dirPath.parent_path() / std::filesystem::path("cinematiques") / dirPath.filename();

    if(!is_directory(dirPath))
        throw std::runtime_error("Not a directory" + dirPath.u8string());

    std::vector<std::filesystem::path> paths;
    for(auto&                          file : std::filesystem::directory_iterator(dirPath))
    {
        paths.push_back(file.path());
    }
    std::sort(paths.begin(),
              paths.end(),
              [](std::filesystem::path p1, std::filesystem::path p2)
              {
                  return p1.filename().string().compare(p2.filename().string()) <= 0;
              });

    for(auto& path : paths)
    {
        images_.emplace_back(RessourceLoader::getTexture(strip_root(path).u8string()));

        centerOrigin(images_.back());
        images_.back().setPosition(WINDOW_SIZE_X / 2.0, WINDOW_SIZE_Y / 2.0);
        fit(images_.back());
    }
}

Cinematique::Cinematique(sf::RenderWindow&       win,
                         std::filesystem::path   dirPath,
                         std::vector<sf::Text>   texts,
                         bool                    waitForSkip,
                         std::unique_ptr<Screen> nextScreen) : Cinematique{
    win,
    dirPath,
    waitForSkip,
    std::move(nextScreen)
}
{
    texts_ = texts;
    for(auto& text : texts_) { centerOrigin(text); }
}

Cinematique::Cinematique(sf::RenderWindow&       win,
                         std::filesystem::path   dirPath,
                         const std::string&      musicName,
                         bool                    waitForSkip,
                         std::unique_ptr<Screen> nextScreen) :
    Cinematique{win, dirPath, waitForSkip, std::move(nextScreen)} { musicName_ = musicName; }

Cinematique::Cinematique(sf::RenderWindow&       win,
                         std::filesystem::path   dirPath,
                         const std::string&      musicName,
                         std::vector<sf::Text>   texts,
                         bool                    waitForSkip,
                         std::unique_ptr<Screen> nextScreen) :
    Cinematique{
        win,
        dirPath,
        texts,
        waitForSkip,
        std::move(nextScreen)
    } { musicName_ = musicName; }

std::unique_ptr<Screen> Cinematique::execute()
{
    if(!musicName_.empty())
        DJ::getInstance().playMusic(musicName_);

    window_.setView(sf::View({0, 0, static_cast<float>(WINDOW_SIZE_X), static_cast<float>(WINDOW_SIZE_Y)}));

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
            while(window_.pollEvent(event))
            {
                auto result = gestionEvent(event);
                if(result)
                    return std::move(*result);

                if(event.type == sf::Event::KeyPressed && ((currentTime <= fadeInTime_ + frameTime_ && !skippingAsked)
                    || waitForSkip_))
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

            window_.clear();
            window_.draw(image);

            for(auto& text : texts_) { window_.draw(text); }

            if(currentTime < fadeInTime_)
            {
                rect_.setFillColor(sf::Color(0, 0, 0, 255 * ((fadeInTime_ - currentTime) / fadeInTime_)));
                window_.draw(rect_);
            }
            else if(currentTime >= fadeInTime_ + frameTime_)
            {
                if(waitForSkip_ && !skipped)
                    currentTime = fadeInTime_ + frameTime_;
                else
                {
                    rect_.setFillColor(sf::Color(0,
                                                 0,
                                                 0,
                                                 255 * ((currentTime - frameTime_ - fadeInTime_) / fadeOutTime_)));
                    window_.draw(rect_);
                }
            }

            if(currentTime >= fadeInTime_ + frameTime_ + fadeOutTime_) { animateFrame = false; }


            currentTime += globalClock::getClock().restart();
            //std::cout << currentTime.asSeconds() << std::endl;

            window_.display();
        }
    }

    return std::move(nextScreen_);
}
