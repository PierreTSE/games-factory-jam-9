#include "camera.hpp"
#include "constantes.hpp"


sf::View scrollCamera(Environment& env, Player& player)
{
    double centerX, centerY;
    
    if(env.width_ * PIXEL_SIZE < WINDOW_SIZE_X)
        centerX = env.width_ * PIXEL_SIZE / 2.0;
    else {
        centerX = player.getPosition().x + TARGET_SPRITE_WIDTH / 2.0;
        centerX = std::clamp(centerX, WINDOW_SIZE_X / 2.0, env.width_ * PIXEL_SIZE - WINDOW_SIZE_X / 2.0);
    }
    
    if(env.height_ * PIXEL_SIZE < WINDOW_SIZE_Y)
        centerY = env.height_ * PIXEL_SIZE / 2.0;
    else {
        centerY = player.getPosition().y + TARGET_SPRITE_HEIGHT / 2.0;
        centerY = std::clamp(centerY, WINDOW_SIZE_Y / 2.0, env.height_ * PIXEL_SIZE - WINDOW_SIZE_Y / 2.0);
    }
    
    return sf::View({(float)centerX, (float)centerY}, {(float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y});
}
