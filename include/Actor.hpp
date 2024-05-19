#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Pos2.hpp"
#include "Graphics.hpp"

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Actor 
{
protected:
	double _x, _y, _vx, _vy;
	int _dir, _nextDir;
	const int _CLIP_WIDTH = 24;
	const int _CLIP_HEIGHT = 24;
	const int _MOVE_DELAY = 50;
public:
	virtual void render(Graphics* graphics, SDL_Texture* spritesheet) = 0;
	virtual void update() = 0;
	virtual void reset() = 0;
	//void setDir(const int dir);
	const int getX() const { return _x; }
	const int getY() const { return _y; }
	const int getDir() const { return _dir; }
	const int getNextDir() const { return _nextDir; }
	const Pos2 getNextPos(const int dir); // returns position vector if valid, (-1,-1) if not valid
};

#endif // ACTOR_HPP
