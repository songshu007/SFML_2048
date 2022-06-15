#include "Game.h"
#include <time.h>

int main()
{
	srand((unsigned)time(NULL));
	Game game;
	game.run();
}