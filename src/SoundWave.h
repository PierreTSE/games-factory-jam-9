#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H

#include <SFML/Graphics.hpp>
#include "Echolocation.h"
#include "globalClock.hpp"

#include <vector>

class SoundWave
{
	private:
		Echolocation echo_;
		sf::CircleShape wave_;
		float radius_;
		float alpha_;
		float radiusSpeed_, alphaSpeed_;
		sf::Vector2f center_;
		sf::Time timer_;
		bool drawCircle = true;
	public:
		SoundWave();
		SoundWave(float x, float y);
		void setCenter(float x, float y);
		void update();
		void setRadiusSpeed(float sp);
		void setAlphaSpeed(float sp);
		void setRadius(float r);
		void setAlpha(float a);
		void draw(sf::RenderWindow &window);
		bool isDead();
		void setDrawCircle(bool b);
		sf::Time getTime();
};


#endif