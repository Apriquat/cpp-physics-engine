#include "Game.h"
#include "Vec2.h"


Game* game = nullptr;

int main(int argc, const char* argv[])
{

	game = new Game();

	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, true);
	
	while (game->running()) {

		game->play();

	}

	game->clean();

	return 0;
}