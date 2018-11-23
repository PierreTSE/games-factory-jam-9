#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H

#include <SFML/Graphics.hpp>

class SoundWave
{
	private:
		sf::CircleShape wave_;
		float radius_;
		float alpha_;
		sf::Vector2f center_;
	public:
		SoundWave(float x, float y);
		void update(sf::Time elapsedTime);
		void draw(sf::RenderWindow &window);
		
};


#endif