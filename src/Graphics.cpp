#include "../include/Graphics.hpp"
#include <SDL2/SDL_image.h>


Graphics::Graphics(const int width, const int height, const std::string& title):
	_width(width),
	_height(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	clear();
	SDL_ShowWindow(_window);
}

Graphics::~Graphics()
{
	for(auto const& itr : _textures)
	{
		SDL_DestroyTexture(itr.second);
	}
	_textures.clear();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}

void Graphics::setDrawColor(const int r, const int g, const int b, const int a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Graphics::clear()
{
	SDL_RenderClear(_renderer);
}

SDL_Texture* Graphics::loadTexture(const std::string& file)
{
	if(_textures.find(file) == _textures.end())
	{
		SDL_Texture* texture = IMG_LoadTexture(_renderer, file.c_str());
		_textures[file] = texture;
		return texture;
	}
	return _textures[file];
}

void Graphics::drawTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst, const double angle)
{
	SDL_Rect transRect = applyTransToRect(dst);
	SDL_RenderCopyEx(_renderer, texture, &src, &transRect, angle, NULL, SDL_FLIP_NONE);
}

void Graphics::drawTexture(SDL_Texture* texture, const SDL_Rect& dst, const double angle)
{
        SDL_Rect transRect = applyTransToRect(dst);
	SDL_RenderCopyEx(_renderer, texture, NULL, &transRect, angle, NULL, SDL_FLIP_NONE);
}

void Graphics::drawTexture(SDL_Texture* texture, const double angle)
{
	SDL_RenderCopyEx(_renderer, texture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
}

void Graphics::drawPoint(const int x, const int y)
{
	SDL_RenderDrawPoint(_renderer, x * _scaleX, y * _scaleY);
}

void Graphics::drawLine(const int x1, const int y1, const int x2, const int y2)
{
	SDL_RenderDrawLine(_renderer, x1 * _scaleX, y1 * _scaleY, x2 * _scaleX, y2 * _scaleY);
}

void Graphics::drawFilledRect(const SDL_Rect& rect)
{
        SDL_Rect transRect = applyTransToRect(rect);
	SDL_RenderFillRect(_renderer, &transRect);
}

void Graphics::update()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::applyTransformation(const double scaleX, const double scaleY) 
{
	_scaleX = scaleX;
	_scaleY = scaleY;
}

SDL_Rect Graphics::applyTransToRect(const SDL_Rect& rect) 
{
	return { (int)(rect.x * _scaleX), (int)(rect.y * _scaleY), (int)(rect.w * _scaleX), (int)(rect.h * _scaleY) };
}
