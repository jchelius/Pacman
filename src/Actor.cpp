#include "../include/Actor.hpp"
#include <cmath>

const Pos2 Actor::getNextPos(const int dir) 
{
	if (dir == NONE) return Pos2(-1, -1);
	int x, y;
	if (dir == UP || dir == DOWN)
	{
		if (int(_x * 2) % 2 == 0) // Do not allow if in between a wall
		{
			return Pos2(-1, -1);
		}
		if (dir == UP)
		{
			y = (int)std::floor(_y); // Row directly above the pacman
			x = (int)std::floor(_x + 0.5); // Column directly above the pacman
		}
		else
		{
			y = (int)std::floor(_y + 0.5) + 1;
			x = (int)std::floor(_x) + 1;
		}
	}
	else if (dir == LEFT || dir == RIGHT)
	{
		if (int(_y * 2) % 2 == 0) // Do not allow if in between a wall
		{
			return Pos2(-1, -1);
		}
		if (dir == RIGHT)
		{
			x = (int)std::floor(_x + 0.5) + 1;
			y = (int)std::floor(_y + 0.5);
		}
		else
		{
			x = (int)std::floor(_x);
			y = (int)std::floor(_y) + 1;
		}
	}
	return Pos2(x, y);
}
