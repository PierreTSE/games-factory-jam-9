#include "Chandelier.h"
#include <fstream>


Chandelier::Chandelier(sf::Vector2i debut, sf::Vector2i fin)
{
    debut_ = debut;
    fin_   = fin;
    objet_ = sf::RectangleShape({2, 2});
    objet_.setPosition({static_cast<float>(debut.x), static_cast<float>(debut.y)});
    objet_.setFillColor(sf::Color::Yellow);
    sens_ = true;
}

std::vector<Chandelier> Chandelier::createChandeliers(std::filesystem::path path)
{
    std::ifstream file(path.c_str(), std::ios::in);
    if(!file.is_open())
        throw std::runtime_error("Can't open from :" + path.u8string());

    std::vector<Chandelier> out;

    int x1, y1, x2, y2;
    while(file >> x1 >> y1 >> x2 >> y2) { out.emplace_back(sf::Vector2i({x1, y1}), sf::Vector2i({x2, y2})); }

    return out;
}

std::vector<Chandelier> Chandelier::createChandeliers(std::filesystem::path path, int ratio)
{
    std::ifstream file(path.c_str(), std::ios::in);
    if(!file.is_open())
        throw std::runtime_error("Can't open from :" + path.u8string());

    std::vector<Chandelier> out;

    int x1, y1, x2, y2;
    while(file >> x1 >> y1 >> x2 >> y2)
    {
        out.emplace_back(sf::Vector2i({x1 * ratio, y1 * ratio}), sf::Vector2i({x2 * ratio, y2 * ratio}));
    }

    return out;
}

void Chandelier::gestion(sf::Time elapsedTime)
{
    const float pas = vitesse_ * elapsedTime.asMilliseconds();

    if(debut_.x != fin_.x)
    {
        if(sens_ && (fin_.x > objet_.getPosition().x || abs(objet_.getPosition().x - fin_.x) < pas))
        {
            objet_.move({pas, 0});
        }
        else if(!sens_ && (debut_.x < objet_.getPosition().x || abs(objet_.getPosition().x - debut_.x) < pas))
        {
            objet_.move({-pas, 0});
        }
        else { sens_ = !sens_; }
    }
    else
    {
        if(sens_ && (fin_.y > objet_.getPosition().y || abs(objet_.getPosition().y - fin_.x) < pas))
        {
            objet_.move({0, pas});
        }
        else if(!sens_ && (debut_.y < objet_.getPosition().y || abs(objet_.getPosition().y - debut_.y) < pas))
        {
            objet_.move({0, -pas});
        }
        else { sens_ = !sens_; }
    }
}

void Chandelier::draw(sf::RenderWindow& window) const { window.draw(objet_); }
