#include "../include/Game.hpp"
#include "../include/Block.hpp"
#include "../include/Pacman.hpp"
#include <iostream>
#include <cmath>
#include <stdlib.h>


Game::Game() :
	_MAX_LIVES(3),
	_SCORE_INC(50),
	_SPRITESHEET("res/images/images.png"),
	_MAP_LOC("res/maps/"),
	_MAP_FILE_EXT(".tmx"),
	_SCREEN_SIZE_RATIO(1.5),
	_BLOCK_CLIP_WIDTH(12),
	_BLOCK_CLIP_HEIGHT(12),
	_LEVEL_WIDTH(28),
	_LEVEL_HEIGHT(31),
	_WINDOW_WIDTH(_LEVEL_WIDTH * _BLOCK_CLIP_WIDTH * _SCREEN_SIZE_RATIO),
	_WINDOW_HEIGHT(_LEVEL_HEIGHT * _BLOCK_CLIP_HEIGHT * _SCREEN_SIZE_RATIO),
	_WINDOW_TITLE("Pacman")
{
	_graphics = new Graphics(_WINDOW_WIDTH, _WINDOW_HEIGHT, _WINDOW_TITLE);
	_graphics->applyTransformation(_SCREEN_SIZE_RATIO, _SCREEN_SIZE_RATIO);
	_input = new Input;
	_pacman = new Pacman;
	_spritesheet = _graphics->loadTexture(_SPRITESHEET);
	int w, h;
	SDL_QueryTexture(_spritesheet, NULL,  NULL, &w, &h);
	_spriteSheetWidth = w / _BLOCK_CLIP_WIDTH;
	_spriteSheetHeight = h / _BLOCK_CLIP_HEIGHT;
	reset();
}

Game::~Game()
{
	_levelData.clear();
	delete _pacman;
	delete _input;
	delete _graphics;
}

void Game::run()
{
	while (!_input->shouldQuit())
	{
		_input->update();
		_graphics->clear();
		update();
		render();
		_graphics->update();
	}
}

void Game::update()
{
	if (_input->isKeyDown(SDL_SCANCODE_LEFT))
	{
		_pacman->setNextDir(LEFT);
	}
	else if (_input->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		_pacman->setNextDir(RIGHT);
	}
	else if (_input->isKeyDown(SDL_SCANCODE_DOWN))
	{
		_pacman->setNextDir(DOWN);
	}
	else if (_input->isKeyDown(SDL_SCANCODE_UP))
	{
		_pacman->setNextDir(UP);
	}
	int pacNextDir = _pacman->getNextDir();
	if (pacNextDir != NONE)
	{
		Pos2 pos2 = _pacman->getNextPos(pacNextDir);
		if (pos2 != Pos2(-1, -1))
		{
			const int boardInd = getBoardInd(pos2);
			if (_levelData[boardInd].getType() != WALL)
			{
				_pacman->setDir(pacNextDir);
			}
		}
	}
	if (SDL_GetTicks() > _pacman->_nextTime)
	{
		_pacman->_nextTime += _pacman->_MOVE_DELAY;
		Pos2 pos2 = _pacman->getNextPos(_pacman->getDir());
		if (pos2 == Pos2(-1, -1))
		{
			_pacman->move(); // move if in between a wall
		}
		else
		{
			const int boardInd = getBoardInd(pos2);
			if (_levelData[boardInd].getType() == REG_PELLET)
			{
				_score += _SCORE_INC;
				_levelData[boardInd].setType(EMPTY);
			}
			else if (_levelData[boardInd].getType() == POWER_PELLET) 
			{
				// TODO: update state of ghosts
				_levelData[boardInd].setType(EMPTY);
			}
			if (_levelData[boardInd].getType() != WALL)
			{
				_pacman->move();
			}
		}
	}
	_pacman->update();
	if (_lives == 0)
	{
		reset();
	}
}

void Game::render()
{
	_pacman->render(_graphics, _spritesheet);
	drawText("Score", _graphics->getWidth() - 100, _graphics->getHeight() - 50);
	for(auto& block : _levelData)
	{
		block.render();
	}
	_graphics->setDrawColor(0, 0, 0);
}

void Game::loadLevel(const int level)
{
	const std::string file = _MAP_LOC + std::to_string(level) + _MAP_FILE_EXT;
	readLevel(file);
}

void Game::readLevel(const std::string& file)
{
	_levelData.clear();
	_levelFile.LoadFile(file.c_str());
	const tinyxml2::XMLElement* firstChElement = _levelFile.FirstChildElement("map");
	const tinyxml2::XMLElement* layer = firstChElement->FirstChildElement("layer");
	const tinyxml2::XMLElement* data = layer->FirstChildElement("data");
	const std::string levelDataStr = data->GetText();
	std::string iStr;
	int i = 0;
	for(auto itr = levelDataStr.begin(); itr < levelDataStr.end(); itr++)
	{
		if(*itr == ',' || itr + 1 == levelDataStr.end())
		{
			BlockType blockType = EMPTY;
			int val = atoi(iStr.c_str());
			if (iStr != "0")
			{
				val--;
				if (val == _POWER_PELLET_LEVEL_ID)
				{
					blockType = POWER_PELLET;
				}
				else if (val == _REG_PELLET_LEVEL_ID) 
				{
					blockType = REG_PELLET;
				}
				else 
				{
					blockType = WALL;
				}
			}
			else
			{
				val = _LEVEL_WIDTH * _LEVEL_HEIGHT;
			}
			const int srcY = (int)std::floor(val / _spriteSheetWidth);
			const int srcX = val - srcY * _spriteSheetWidth;
			const int srcW = _BLOCK_CLIP_WIDTH;
			const int srcH = _BLOCK_CLIP_HEIGHT;
			const SDL_Rect src = { srcX, srcY, srcW, srcH };
			const int dstX = i % _LEVEL_WIDTH;
			const int dstY = (int)std::floor(i / _LEVEL_WIDTH);
			const int dstW = _BLOCK_CLIP_WIDTH;
			const int dstH = _BLOCK_CLIP_HEIGHT;
			const SDL_Rect dst = { dstX, dstY, dstW, dstH };
			Block block(this, src, dst, blockType);
			_levelData.push_back(block);
			iStr.clear();
			i++;
		}
		else if(*itr != ' ' && *itr != '\n')
		{
			iStr.push_back(*itr);
		}
	}
}

void Game::reset()
{
	_lives = _MAX_LIVES;
	loadLevel(1);
	_score = 0;
	_pacman->reset();
}

const BlockType Game::getBlockTypeAtPos(const int x, const int y) const
{
	const int index = y * _LEVEL_WIDTH + x;
	const Block block = _levelData[index];
	return block.getType();
}

void Game::drawText(const std::string& str, const int x, const int y)
{
	int chX = 0;
	for(auto const& ch : str)
	{
		int row, col;
		if (ch >= '0' && ch <= '9')
		{
			col = ch - '0';
			row = 0;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			col = ch - 'A' + 1;
			row = 2;
		}
		else if (ch >= 'a' && ch <= 'z')
		{
			col = ch - 'a' + 1;
			row = 2;
		}
		else 
		{
			continue;
		}
		SDL_Rect src = { col * _BLOCK_CLIP_WIDTH, row * _BLOCK_CLIP_HEIGHT, _BLOCK_CLIP_WIDTH, _BLOCK_CLIP_HEIGHT };
		SDL_Rect dst = { x + chX * _BLOCK_CLIP_WIDTH, y, _BLOCK_CLIP_WIDTH, _BLOCK_CLIP_HEIGHT };
		_graphics->drawTexture(_spritesheet, src, dst);
		chX++;
	}
}
