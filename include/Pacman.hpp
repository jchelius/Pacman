#ifndef PACMAN_H
#define PACMAN_H

#include "Actor.hpp"

#include <array>

class Pacman : public Actor
{
	friend class Game;
private:
	const std::array<int, 4> _LEFT_ANIM_LIST = { 0, 3, 2, 3 };
	const std::array<int, 4> _RIGHT_ANIM_LIST = { 4, 3, 6, 3 };
	const std::array<int, 4> _DOWN_ANIM_LIST = { 5, 3, 7, 3 };
	const std::array<int, 4> _UP_ANIM_LIST = { 1, 3, 3, 3 };
	const std::array<int, 4> _NONE_ANIM_LIST = { 0, 7, 0, 7 };
	const double _START_X = 13;
	const double _START_Y = 22.5;
	unsigned _nextTime;
	unsigned _startTime;
	int _currentAnim;
	std::array<int, 4> _currentAnimList;
	bool _justEnteredPortal;
public:
	Pacman();
	~Pacman(){ }
	void update();
	void render(Graphics* graphics, SDL_Texture* spritesheet);
	void reset();
	void move();
	void setDir(const int dir);
	void setNextDir(const int dir) { _nextDir = dir; }
private:
	void switchAnim();
};


#endif //PACMAN_H