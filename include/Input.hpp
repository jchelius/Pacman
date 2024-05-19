#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>


class Input
{
private:
	const Uint8* _keys;
	bool _shouldQuit;
public:
	Input();
	~Input(){ }
	void update();
	const bool shouldQuit() const { return _shouldQuit; }
	const SDL_Keycode isKeyDown(const SDL_Scancode key) const { return _keys[key]; }
	const int getMousePosX();
	const int getMousePosY();
};


#endif //INPUT_H