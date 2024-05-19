#ifndef GHOST_HPP
#define GHOST_HPP

#include "Actor.hpp"

enum GhostColor
{
	RED,
	PINK,
	BLUE,
	ORANGE
};

class Ghost : public Actor 
{
private:
	const std::pair<int, int> _LEFT_ANIM_LIST = { 4, 5 };
	const std::pair<int, int> _RIGHT_ANIM_LIST = { 0, 1 };
	const std::pair<int, int> _DOWN_ANIM_LIST = { 2, 3 };
	const std::pair<int, int> _UP_ANIM_LIST = { 6, 7 };
	std::pair<int, int> _clipStartPos;
	std::pair<int, int> _currentAnimList;
	int _currentAnimFrame;
	int _color;
private:
	void switchAnim();
public:
	Ghost(int color);
	void render(Graphics* graphics, SDL_Texture* spritesheet);
	void update();
	void reset();
};

#endif // GHOST_HPP