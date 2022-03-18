#ifndef SDL_MAIN_MANDLED
#define SDL_MAIN_HANDLED // Macro must be included before any SDL files
#endif // !SDL_MAIN_MANDLED

#include "Window.h"
#include "Game.h"

int main()
{
	Window wnd("Tic Tac Toe", 800, 800);

	Game the_game(wnd);

	return the_game.Run();
}