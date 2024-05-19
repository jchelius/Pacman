#ifndef BLOCK_H
#define BLOCK_H

//A little class to store the geometry of each block

#include "Graphics.hpp"

class Game;

enum BlockType
{
	EMPTY,
	WALL,
	REG_PELLET,
	POWER_PELLET
};

class Block
{
private:
	SDL_Rect _srcRect;
	SDL_Rect _dstRect;
	const int _x, _y;
	const int _srcX, _srcY;
	Game* _game;
	BlockType _type;
public:
	Block(Game* game, const SDL_Rect& srcRect, const SDL_Rect& dstRect, BlockType type);
	~Block(){ }
	void render();
	const int getX() const { return _x; }
	const int getY() const { return _y; }
	const BlockType getType() const { return _type; }
	void setType(const BlockType newType) { _type = newType; }
};


#endif //BLOCK_H
