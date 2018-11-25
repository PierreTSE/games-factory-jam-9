#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "environment/Environment.hpp"

typedef struct {
	bool top, bot, right, left;
} Wall;


class Maze
{
private:
	std::vector<std::vector<Wall>> walls_;
public:
	Maze(Environment &env);
	Wall getWall(int i, int j);
	size_t getWidth();
	size_t getHeight();
	void parseWall(Environment &env);
};

#endif // !MAZE_H
