#include "../include/Game.hpp"
#include "../include/Random.hpp"


const int WIDTH = 336 * 2;
const int HEIGHT = 372 * 2;
const std::string TITLE = "Pacman";


int main(int, char**)
{
	Game game;
	game.run();
	return 0;
}