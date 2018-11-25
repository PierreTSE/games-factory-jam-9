#include "Bell.h"

Bell& Bell::getInstance()
{
	return bellInstance;
}

bool Bell::checkReady(sf::Time cooldown)
{
	return (soundwaves_.size() == 0 || soundwaves_.back().getTime() > cooldown);
}

void Bell::draw(sf::RenderWindow &window)
{
	for (size_t i = 0; i < soundwaves_.size(); i++)
	{
		soundwaves_[i].update();
		soundwaves_[i].draw(window);
	}

	soundwaves_.erase(std::remove_if(soundwaves_.begin(),
									 soundwaves_.end(),
								     [](auto& elem) { return elem.isDead(); }),
									 soundwaves_.end());
}


void Bell::add(Maze * maze, Item *sortie, float centerX, float centerY, float radius, float alpha, float radiusSpeed, float alphaSpeed, bool drawCircle)
{
	soundwaves_.emplace_back(maze, sortie, centerX, centerY);
	soundwaves_.back().setAlphaSpeed(alphaSpeed);
	soundwaves_.back().setAlpha(alpha);
	soundwaves_.back().setRadiusSpeed(radiusSpeed);
	soundwaves_.back().setRadius(radius);
	soundwaves_.back().setDrawCircle(drawCircle);
}
