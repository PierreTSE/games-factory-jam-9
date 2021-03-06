#ifndef BELL_H
#define BELL_H

#include "SoundWave.h"
#include "Maze.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Bell
{
	private:
		std::vector<SoundWave> soundwaves_;
	public:
		Bell() = default;
		static Bell& getInstance();
		bool checkReady(sf::Time cooldown);
		void draw(sf::RenderWindow &window);
		void clear();
		void add(Maze *maze, Item *item, float centerX, float centerY, float radius = 0, float alpha = 255, float radiusSpeed = 600, float alphaSpeed = 600, bool drawCircle = true);
};

static Bell bellInstance;

#endif