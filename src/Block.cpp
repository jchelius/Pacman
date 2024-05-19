#include "../include/Block.hpp"
#include "../include/Game.hpp"


Block::Block(Game* game, const SDL_Rect& srcRect, const SDL_Rect& dstRect, BlockType type):
	_x(dstRect.x),
	_y(dstRect.y),
	_srcX(srcRect.x),
	_srcY(srcRect.y),
	_game(game),
	_type(type)
{
	_srcRect = { _srcX * srcRect.w, _srcY * srcRect.h, srcRect.w, srcRect.h };
	_dstRect = { _x * dstRect.w, _y * dstRect.h, dstRect.w, dstRect.h };
}

void Block::render()
{
	if(_type != EMPTY)
		_game->getGraphics()->drawTexture(_game->getSpritesheetTexture(), _srcRect, _dstRect);
}
