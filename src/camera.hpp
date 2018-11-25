#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include "environment/Environment.hpp"
#include "Character.h"


sf::View scrollCamera(Environment& env, Player& player);

#endif // CAMERA_HPP