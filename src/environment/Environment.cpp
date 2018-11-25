#include "Environment.hpp"

void Environment::updatePillars()
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

void Environment::load(std::filesystem::path path)
{
    sf::Image img;
    if(!img.loadFromFile(path.u8string()))
        throw std::runtime_error("Can't load image from path :" + path.u8string());

    width  = img.getSize().x;
    height = img.getSize().y;

    //initialize
    maze_ = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
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
            else if(img.getPixel(j, i) == sf::Color(0, 255, 0)) { bonus_.emplace_back(j, i); }

                //luciole cyan
            else
                if(img.getPixel(j, i) == sf::Color(0, 255, 255)) { dallesLuciole_.emplace_back(j, i); }
        }
    }

    obstacles_ = maze_;
    updatePillars();
}

void Environment::switchPillars()
{
    for(auto& pillar : pillars_)
        pillar.isUp_ = !pillar.isUp_;
    updatePillars();
}

void Environment::switchPillar(size_t i)
{
    pillars_.at(i).isUp_ = !pillars_.at(i).isUp_;
    updatePillars();
}

void Environment::drawObstacles(sf::RenderWindow& window, float ratio, sf::Vector2f origin) const
{
    for(int i = 0 ; i < height ; ++i)
    {
        for(int j = 0 ; j < height ; ++j)
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

void Environment::drawColorized(sf::RenderWindow& window, float ratio, sf::Vector2f origin) const
{
    for(int i = 0 ; i < height ; ++i)
    {
        for(int j = 0 ; j < height ; ++j)
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

template<typename T>
bool Environment::isBonusOrigin(sf::Vector2<T> inputPos) const
{
    sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

    if(std::find(bonus_.begin(), bonus_.end(), pos) != bonus_.end())
        return true;

    return false;
}

template<typename T>
bool Environment::isDalleOrigin(sf::Vector2<T> inputPos) const
{
    sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

    if(std::find(dallesLuciole_.begin(), dallesLuciole_.end(), pos) != dallesLuciole_.end())
        return true;

    return false;
}

template<typename T>
bool Environment::isPillarState(sf::Vector2<T> inputPos, bool isUp) const
{
    sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

    return (std::find_if(pillars_.begin(),
                         pillars_.end(),
                         [pos, isUp](Pillar p) { return (p.pos_ == pos && p.isUp_ == isUp); }) != pillars_.
        end());
}

template<typename T>
bool Environment::is_in_depart(sf::Vector2<T> inputPos) const
{
    sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

    if(std::find(depart_.begin(), depart_.end(), pos) != depart_.end())
        return true;

    return false;
}

template<typename T>
bool Environment::is_in_arrivee(sf::Vector2<T> inputPos) const
{
    sf::Vector2i pos = {static_cast<int>(inputPos.x), static_cast<int>(inputPos.y)};

    if(std::find(arrivee_.begin(), arrivee_.end(), pos) != arrivee_.end())
        return true;

    return false;
}

template<typename T>
bool Environment::is_in_bonus(sf::Vector2<T> pos) const
{
    return isBonusOrigin(pos) || isBonusOrigin(pos + sf::Vector2<T>({-1, 0})) ||
            isBonusOrigin(pos + sf::Vector2<T>({0, -1})) || isBonusOrigin(pos + sf::Vector2<T>({-1, -1}));
}

template<typename T>
bool Environment::is_in_dalle(sf::Vector2<T> inputPos) const
{
    return isDalleOrigin(inputPos) || isDalleOrigin(inputPos + sf::Vector2<T>({-1, 0})) ||
            isDalleOrigin(inputPos + sf::Vector2<T>({0, -1})) || isDalleOrigin(inputPos + sf::Vector2<T>({-1, -1}));
}

