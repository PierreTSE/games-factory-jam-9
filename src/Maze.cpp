#include "Maze.h"

Maze::Maze(Environment &env)
{
	parseWall(env);
}

Wall Maze::getWall(int i, int j)
{
	return walls_[i][j];
}

size_t Maze::getWidth()
{
	return walls_.size();
}

size_t Maze::getHeight()
{
	return walls_.front().size();
}

void Maze::parseWall(Environment & env)
{
	auto vect = env.getObstacles();
	walls_.resize(env.width_);
	for (size_t i = 0; i < walls_.size(); i++)
	{
		walls_[i].resize(env.height_);
		for (size_t j = 0; j < walls_[i].size(); j++)
		{
			if (i == 0 || j == 0 || i == env.height_ - 1 || j == env.width_ - 1)
			{
				walls_[i][j].top = false;
				walls_[i][j].bot = false;
				walls_[i][j].left = false;
				walls_[i][j].right = false;
			}
			else
			{
				if (vect[i][j])
				{
					walls_[i][j].top = !vect[i - 1][j];
					walls_[i][j].bot = !vect[i + 1][j];
					walls_[i][j].left = !vect[i][j - 1];
					walls_[i][j].right = !vect[i][j + 1];
				}
				else
				{
					walls_[i][j].top = false;
					walls_[i][j].bot = false;
					walls_[i][j].left = false;
					walls_[i][j].right = false;
				}
			}


		}
	}
}
