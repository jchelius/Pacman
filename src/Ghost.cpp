#include "../include/Ghost.hpp"

Ghost::Ghost(int color)
{
	switch(color)
	{
	case RED:
		_clipStartPos = { 0, 6 };
		break;
	case PINK:
		_clipStartPos = { 0, 8 };
		break;
	case BLUE:
		_clipStartPos = { 8, 8 };
		break;
	case ORANGE:
		_clipStartPos = { 0, 9 };
		break;
	}
}

void Ghost::switchAnim() 
{
	if (_currentAnimFrame == _currentAnimList.first) 
	{
		_currentAnimFrame = _currentAnimList.second;
	}
	else
	{
		_currentAnimFrame = _currentAnimList.first;
	}
}

void Ghost::render(Graphics* graphics, SDL_Texture* spritesheet)
{
	int srcX = _currentAnimList.first + _clipStartPos.first;
	int srcY = _currentAnimList.second + _clipStartPos.second;
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

void Ghost::update() 
{
	
}

void Ghost::reset() 
{
	
}