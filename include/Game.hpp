#ifndef GAME_H
#define GAME_H

#include "Graphics.hpp"
#include "Input.hpp"
#include "Pos2.hpp"
#include "Actor.hpp"
#include "Block.hpp"

#include "tinyxml2/tinyxml2.hpp"

#include <vector>

// class Block;
class Pacman;
// enum BlockType;

class Game
{
private:
	int _level;
	int _lives;
	int _score;
	const int _MAX_LIVES, _SCORE_INC;
	const std::string _SPRITESHEET;
	const std::string _MAP_LOC;
	const std::string _MAP_FILE_EXT;
	const double _SCREEN_SIZE_RATIO;
	const int _BLOCK_CLIP_WIDTH, _BLOCK_CLIP_HEIGHT;
	const int _LEVEL_WIDTH, _LEVEL_HEIGHT;
	const int _WINDOW_WIDTH, _WINDOW_HEIGHT;
	const std::string _WINDOW_TITLE;
	const int _POWER_PELLET_LEVEL_ID = 18;
	const int _REG_PELLET_LEVEL_ID = 16;
	int _spriteSheetWidth, _spriteSheetHeight;
	std::vector<Block> _levelData;
	tinyxml2::XMLDocument _levelFile;
	SDL_Texture* _spritesheet;
	Input* _input;
	Graphics* _graphics;
	Pacman* _pacman;
public:
	Game();
	~Game();
	void run();
	void update();
	void render();
	const BlockType getBlockTypeAtPos(const int x, const int y) const;
	const double getScreenSizeRatio() const { return _SCREEN_SIZE_RATIO; }
	SDL_Texture* getSpritesheetTexture() const { return _spritesheet; }
	Graphics* getGraphics() { return _graphics; }
private:
	const int getBoardInd(const Pos2& pos) { return pos.y * _LEVEL_WIDTH + pos.x; }
	void loadLevel(const int level);
	void readLevel(const std::string& file);
	void reset();
	void drawText(const std::string& str, const int x, const int y);
};


#endif //GAME_H
