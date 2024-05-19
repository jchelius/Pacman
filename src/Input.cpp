#include "../include/Input.hpp"


Input::Input():
	_shouldQuit(false)
{
	_keys = SDL_GetKeyboardState(NULL);
}

void Input::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			_shouldQuit = true;
		}
	}
}

const int Input::getMousePosX()
{
	int x;
	SDL_GetMouseState(&x, NULL);
	return x;
}

const int Input::getMousePosY()
{
	int y;
	SDL_GetMouseState(NULL, &y);
	return y;
}