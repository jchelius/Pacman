#include "../include/Pacman.hpp"
#include "../include/Game.hpp"
#include "../include/Block.hpp"
#include <iostream>


Pacman::Pacman():
	_nextTime(0),
	_startTime(0),
	_currentAnim(0),
	_currentAnimList(_NONE_ANIM_LIST),
	_justEnteredPortal(false)
{

}

void Pacman::update()
{
	if(_x == 26.5 && !_justEnteredPortal)
	{
		_x = -1;
		_justEnteredPortal = true;
	}
	else if(_x == -0.5 && !_justEnteredPortal)
	{
		_x = 27;
		_justEnteredPortal = true;
	}
}

void Pacman::move() 
{
	if (_justEnteredPortal && ((_x > -0.5 && _x < 1) || (_x < 26.5 && _x > 25))) _justEnteredPortal = false;
	_x += 0.5 * _vx;
	_y += 0.5 * _vy;
	switchAnim();
}

void Pacman::switchAnim()
{
	if (_currentAnim == 2)
	{
		_currentAnim = 0;
	}
	else if (_currentAnim == 0)
	{
		_currentAnim = 2;
	}
}

void Pacman::render(Graphics* graphics, SDL_Texture* spritesheet)
{
	int srcX = _currentAnimList[_currentAnim];
	int srcY = _currentAnimList[_currentAnim + 1];
	int srcW = _CLIP_WIDTH;
	int srcH = _CLIP_HEIGHT;
	SDL_Rect clip = { srcW * srcX, srcH * srcY, srcW, srcH };
	int dstX = (int)((_x * srcW / 2));
	int dstY = (int)(((_y * srcH / 2) + 1));
	int dstW = srcW;
	int dstH = srcH;
	SDL_Rect dst = { dstX, dstY, dstW, dstH };
	graphics->drawTexture(spritesheet, clip, dst);
}

void Pacman::reset()
{
	_currentAnim = 0;
	_x = _START_X;
	_y = _START_Y;
	setDir(NONE);
	_nextTime = SDL_GetTicks();
	_startTime = _nextTime;
}

void Pacman::setDir(const int dir)
{
	_nextDir = NONE;
	_dir = dir;
	switch (dir)
	{
	case DOWN:
		_currentAnimList = _DOWN_ANIM_LIST;
		_vy = 1;
		_vx = 0;
		break;
	case UP:
		_currentAnimList = _UP_ANIM_LIST;
		_vy = -1;
		_vx = 0;
		break;
	case RIGHT:
		_currentAnimList = _RIGHT_ANIM_LIST;
		_vy = 0;
		_vx = 1;
		break;
	case LEFT:
		_currentAnimList = _LEFT_ANIM_LIST;
		_vy = 0;
		_vx = -1;
		break;
	case NONE:
		_currentAnimList = _NONE_ANIM_LIST;
		_vy = 0;
		_vx = 0;
		break;
	}
}
