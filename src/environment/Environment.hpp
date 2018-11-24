#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <filesystem>
#include <SFML/Graphics/Texture.hpp>

struct Pillar
{
    sf::Vector2i pos_;

    bool isUp_ = true;

    Pillar(sf::Vector2i pos, bool isUp = true)
    {
        pos_  = pos;
        isUp_ = isUp;
    }
};


class Environment
{
private:
    // Attributes

    //obstacles
    std::vector<Pillar>            pillars_;
    std::vector<std::vector<bool>> maze_;
    std::vector<std::vector<bool>> obstacles_;

    //interactive
    std::vector<sf::Vector2i> depart_;
    std::vector<sf::Vector2i> arrivee_;
    std::vector<sf::Vector2i> bonus_;

    //Methods

    bool isBonusOrigin(sf::Vector2f inputPos) const
    {
        sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

        if(std::find(bonus_.begin(), bonus_.end(), pos) != bonus_.end())
            return true;

        return false;
    }

    bool isBonusOrigin(sf::Vector2i inputPos) const
    {
        return isBonusOrigin(sf::Vector2f(static_cast<float>(inputPos.x), static_cast<float>(inputPos.y)));
    }

    bool isPillarState(sf::Vector2f inputPos, bool isUp) const
    {
        sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

        return (std::find_if(pillars_.begin(),
                             pillars_.end(),
                             [pos, isUp](Pillar p) { return (p.pos_ == pos && p.isUp_ == isUp); }) != pillars_.
            end());
    }

    bool isPillarState(sf::Vector2i inputPos, bool isUp) const
    {
        return isPillarState(sf::Vector2f(static_cast<float>(inputPos.x), static_cast<float>(inputPos.y)), isUp);
    }

    void updatePillars()
    {
        obstacles_ = maze_;

        for(auto& pillar : pillars_)
        {
            if(!pillar.isUp_)
            {
                //to use "opened" pillar door as obstacle
                /*
                for(int i = 0 ; i < 4 ; i++)
                {
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        if((i == 1 && (j != 0 && j != 3)) || (i == 2 && (j != 0 && j != 3)))
                            continue;

                        const size_t x = pillar.pos_.x + j - 1;
                        const size_t y = pillar.pos_.y + i - 1;

                        obstacles_[y][x] = true;
                    }
                }
                */
            }
            else
            {
                for(int i = 0 ; i <= 1 ; i++)
                {
                    for(int j = 0 ; j <= 1 ; j++)
                    {
                        const size_t x = pillar.pos_.x + j;
                        const size_t y = pillar.pos_.y + i;

                        obstacles_[y][x] = true;
                    }
                }
            }
        }
    }

public :
    size_t width_  = 0;
    size_t height_ = 0;

    // Methods
    void load(std::filesystem::path path)
    {
        sf::Image img;
        if(!img.loadFromFile(path.u8string()))
            throw std::runtime_error("Can't load image from path :" + path.u8string());

        width_  = img.getSize().x;
        height_ = img.getSize().y;

        //initialize
        maze_ = std::vector<std::vector<bool>>(width_, std::vector<bool>(height_, false));
        depart_.clear();
        arrivee_.clear();

        for(int i = 0 ; i < img.getSize().x ; ++i)
        {
            for(int j = 0 ; j < img.getSize().y ; ++j)
            {
                //walls noir
                if(img.getPixel(j, i) == sf::Color::Black)
                    maze_[i][j] = true;

                    //pillars rose
                else if(img.getPixel(j, i) == sf::Color(255, 0, 255))
                {
                    j++;
                    if(j >= img.getSize().x)
                        throw std::runtime_error("oob x : " + std::to_string(j) + " at line : " + std::to_string(i));

                    if(img.getPixel(j, i) == sf::Color(255, 0, 255)) { pillars_.push_back(Pillar({j, i + 1}, false)); }
                    else { pillars_.push_back(Pillar({j - 1, i}, true)); }
                }

                    //depart bleu
                else if(img.getPixel(j, i) == sf::Color(0, 0, 255)) { depart_.emplace_back(j, i); }

                    //arivee rouge
                else if(img.getPixel(j, i) == sf::Color(255, 0, 0)) { arrivee_.emplace_back(j, i); }

                    //bonus
                else
                    if(img.getPixel(j, i) == sf::Color(0, 255, 0)) { bonus_.emplace_back(j, i); }
            }
        }

        obstacles_ = maze_;
        updatePillars();
    }

    std::vector<std::vector<bool>> getObstacles() const { return obstacles_; }

    bool is_in_depart(sf::Vector2f inputPos) const
    {
        sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

        if(std::find(depart_.begin(), depart_.end(), pos) != depart_.end())
            return true;

        return false;
    }

    bool is_in_arrivee(sf::Vector2f inputPos) const
    {
        sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

        if(std::find(arrivee_.begin(), arrivee_.end(), pos) != arrivee_.end())
            return true;

        return false;
    }

    bool is_in_depart(sf::Vector2i inputPos) const
    {
        return is_in_depart(sf::Vector2f(static_cast<float>(inputPos.x), static_cast<float>(inputPos.y)));
    }

    bool is_in_arrivee(sf::Vector2i inputPos) const
    {
        return is_in_arrivee(sf::Vector2f(static_cast<float>(inputPos.x), static_cast<float>(inputPos.y)));
    }

    bool is_in_bonus(sf::Vector2f pos) const
    {
        return isBonusOrigin(pos) || isBonusOrigin(pos + sf::Vector2f({-1, 0})) ||
                isBonusOrigin(pos + sf::Vector2f({0, -1})) || isBonusOrigin(pos + sf::Vector2f({-1, -1}));
    }

    bool is_in_bonus(sf::Vector2i inputPos) const
    {
        return is_in_bonus(sf::Vector2f(static_cast<float>(inputPos.x), static_cast<float>(inputPos.y)));
    }

    void switchPillars()
    {
        for(auto& pillar : pillars_)
            pillar.isUp_ = !pillar.isUp_;
        updatePillars();
    }

    void switchPillar(size_t i)
    {
        pillars_.at(i).isUp_ = !pillars_.at(i).isUp_;
        updatePillars();
    }

    void drawObstacles(sf::RenderWindow& window, float ratio, sf::Vector2f origin = {1.f, 1.f}) const
    {
        for(int i = 0 ; i < height_ ; ++i)
        {
            for(int j = 0 ; j < height_ ; ++j)
            {
                const sf::Vector2i pos(j, i);

                sf::RectangleShape rect({ratio, ratio});
                rect.setPosition((j + origin.x) * ratio, (i + origin.y) * ratio);

                if(is_in_arrivee(pos))
                    rect.setFillColor(sf::Color::Red);
                else if(is_in_depart(pos))
                    rect.setFillColor(sf::Color::Blue);
                else if(is_in_bonus(pos))
                    rect.setFillColor(sf::Color::Green);
                else if(obstacles_[i][j])
                    rect.setFillColor(sf::Color::Black);


                window.draw(rect);
            }
        }
    }

    void drawColorized(sf::RenderWindow& window, float ratio, sf::Vector2f origin = {1.f, 1.f}) const
    {
        for(int i = 0 ; i < height_ ; ++i)
        {
            for(int j = 0 ; j < height_ ; ++j)
            {
                const sf::Vector2i pos(j, i);

                sf::RectangleShape rect({ratio, ratio});
                rect.setPosition((j + origin.x) * ratio, (i + origin.y) * ratio);

                if(is_in_arrivee(pos))
                    rect.setFillColor(sf::Color::Red);
                else if(is_in_depart(pos))
                    rect.setFillColor(sf::Color::Blue);

                else if(maze_[i][j])
                    rect.setFillColor(sf::Color::Black);

                window.draw(rect);
            }

            for(auto& pillar : pillars_)
            {
                if(!pillar.isUp_)
                {
                    for(int i = 0 ; i < 4 ; i++)
                    {
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            if((i == 1 && (j != 0 && j != 3)) || (i == 2 && (j != 0 && j != 3)))
                                continue;

                            const size_t x = pillar.pos_.x + j - 1;
                            const size_t y = pillar.pos_.y + i - 1;

                            sf::Vector2i pos(x, y);

                            sf::RectangleShape rect({ratio, ratio});
                            rect.setPosition((x + origin.x) * ratio, (y + origin.y) * ratio);
                            rect.setFillColor(sf::Color(255, 0, 255));

                            window.draw(rect);
                        }
                    }
                }
                else
                {
                    const sf::Vector2f pos(pillar.pos_.x, pillar.pos_.y);
                    for(int            i = 0 ; i <= 1 ; i++)
                    {
                        for(int j = 0 ; j <= 1 ; j++)
                        {
                            const size_t x = pillar.pos_.x + j;
                            const size_t y = pillar.pos_.y + i;

                            sf::Vector2i pos(x, y);

                            sf::RectangleShape rect({ratio, ratio});
                            rect.setPosition((x + origin.x) * ratio, (y + origin.y) * ratio);
                            rect.setFillColor(sf::Color(255, 0, 255));
                            window.draw(rect);
                        }
                    }
                }
            }

            for(auto& pos : bonus_)
            {
                for(int i = 0 ; i <= 1 ; i++)
                {
                    for(int j = 0 ; j <= 1 ; j++)
                    {
                        const size_t x = pos.x + j;
                        const size_t y = pos.y + i;

                        sf::Vector2i pos(x, y);

                        sf::RectangleShape rect({ratio, ratio});

                        rect.setPosition((pos.x + origin.x) * ratio, (pos.y + origin.y) * ratio);
                        rect.setFillColor(sf::Color(0, 255, 0));
                        window.draw(rect);
                    }
                }
            }
        }
    }
};

#endif // ENVIRONMENT_HPP
