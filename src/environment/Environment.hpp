#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "../RessourceLoader.hpp"
#include "../constantes.hpp"


struct Pillar
{
    sf::Vector2i pos_;

    bool isUp_ = true;

	sf::Sprite up_;
	sf::Sprite down_;

    Pillar(sf::Vector2i pos, bool isUp = true)
    {
		up_ = sf::Sprite(RessourceLoader::getTexture("sprites/sprite_bascule_fermee.png"));
		down_ = sf::Sprite(RessourceLoader::getTexture("sprites/sprite_bascule_ouverte.png"));
        pos_  = pos;
        isUp_ = isUp;

		up_.setPosition(((pos_.x-0.5) * PIXEL_SIZE - 10), ((pos_.y-0.5) * PIXEL_SIZE - 10));
		down_.setPosition(((pos_.x-0.5) * PIXEL_SIZE - 10)-4, ((pos_.y-0.5) * PIXEL_SIZE - 10));

		up_.setScale(0.7f, 0.7f);
		down_.setScale(0.7f, 0.7f);
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
    std::vector<sf::Vector2i> dallesLuciole_;

    //Player elements
    int nbRingMap_;

    //Methods

    template<typename T>
    bool isBonusOrigin(sf::Vector2<T> inputPos) const;

    template<typename T>
    bool isDalleOrigin(sf::Vector2<T> inputPos) const;

    template<typename T>
    bool isPillarState(sf::Vector2<T> inputPos, bool isUp) const;

    void updatePillars();

public :
    size_t width  = 0;
    size_t height = 0;

    // Methods
    void load(std::filesystem::path path);

    Environment() = default;

    explicit Environment(std::filesystem::path path) { load(std::move(path)); }

    //switch binary doors

    void switchPillars();

    void switchPillar(size_t i);

    //getters

    std::vector<std::vector<bool>> const& getObstacles() const { return obstacles_; }

    std::vector<sf::Vector2i> const& getDepart() const { return depart_; }

    std::vector<sf::Vector2i> const& getArrivee() const { return arrivee_; }

	std::vector<sf::Vector2i> const& getBonus() const { return bonus_; }

    std::vector<sf::Vector2i> const& getDalles() const { return dallesLuciole_; }

    int getMapLife() const { return nbRingMap_; }

    // testers

    template<typename T>
    bool is_in_depart(sf::Vector2<T> inputPos) const;

    template<typename T>
    bool is_in_arrivee(sf::Vector2<T> inputPos) const;

    template<typename T>
    bool is_in_bonus(sf::Vector2<T> pos) const;

    template<typename T>
    bool is_in_dalle(sf::Vector2<T> inputPos) const;

	void drawPillars(sf::RenderWindow &render);

    //méthodes de test, ne sont pas dans le jeu

    void drawObstacles(sf::RenderWindow& window, float ratio, sf::Vector2f origin = {1.f, 1.f}) const;

    void drawColorized(sf::RenderWindow& window, float ratio, sf::Vector2f origin = {1.f, 1.f}) const;
};

#endif // ENVIRONMENT_HPP
