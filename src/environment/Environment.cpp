#include "Environment.hpp"

void Environment::updatePillars() {
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

void Environment::drawObstacles(sf::RenderWindow & window, float ratio, sf::Vector2f origin) const
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
                else if(is_in_dalle(pos))
                    rect.setFillColor(sf::Color::Cyan);
                else if(obstacles_[i][j])
                    rect.setFillColor(sf::Color::Black);


                window.draw(rect);
            }
        }
    }

void Environment::drawColorized(sf::RenderWindow & window, float ratio, sf::Vector2f origin) const
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
