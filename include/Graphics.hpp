#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <string>
#include <map>


class Graphics
{
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	const int _width, _height;
	double _scaleX, _scaleY;
	std::map<std::string, SDL_Texture*> _textures;
private:
	SDL_Rect applyTransToRect(const SDL_Rect& rect);
public:
	Graphics(const int width, const int height, const std::string& title = "Game");
	~Graphics();
	const int getWidth() const { return _width; }
	const int getHeight() const { return _height; }
	void setDrawColor(const int r, const int g, const int b, const int a = 255);
	void clear();
	SDL_Texture* loadTexture(const std::string& file);
	void drawTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst, const double angle = 0);
	void drawTexture(SDL_Texture* texture, const SDL_Rect& dst, const double angle = 0);
	void drawTexture(SDL_Texture* texture, const double angle = 0);
	void drawPoint(const int x, const int y);
	void drawLine(const int x1, const int y1, const int x2, const int y2);
	void drawFilledRect(const SDL_Rect& rect);
	void update();
	void applyTransformation(const double scaleX, const double scaleY);
};


#endif //GRAPHICS_H