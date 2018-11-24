#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H

#include <SFML/Graphics.hpp>
#include "Echolocation.h"


#include <vector>

class SoundWave
{
	private:
		Echolocation echo_;
		sf::CircleShape wave_;
		float radius_;
		float alpha_;
		sf::Vector2f center_;
		sf::Time timer_;
	public:
		SoundWave();
		SoundWave(float x, float y);
		void setCenter(float x, float y);
		void update(sf::Time elapsedTime);
		void draw(sf::RenderWindow &window);
		bool isDead();
		sf::Time getTime();
};


#endif