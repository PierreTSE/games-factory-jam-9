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
	walls_.resize(env.width);
	for (size_t i = 0; i < walls_.size(); i++)
	{
		walls_[i].resize(env.height);
		for (size_t j = 0; j < walls_[i].size(); j++)
		{
			if (i == 0 || j == 0 || i == env.height - 1 || j == env.width - 1)
			{
				walls_[i][j].top = false;
				walls_[i][j].bot = false;
				walls_[i][j].left = false;
				walls_[i][j].right = false;

				if (i != j && !(i == 0 && j == env.width - 1) && !(i == env.height - 1 && j == 0))
				{
					if (i == 0 && !vect[i + 1][j])
						walls_[i][j].bot = true;
					if (j == 0 && !vect[i][j + 1])
						walls_[i][j].right = true;
					if (i == env.height - 1 && !vect[i - 1][j])
						walls_[i][j].top = true;
					if (j == env.width - 1 && !vect[i][j - 1])
						walls_[i][j].left = true;
				}
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
