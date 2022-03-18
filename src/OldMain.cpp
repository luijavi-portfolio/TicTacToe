#include <SDL.h>

/* Classes for game
* TODO: To be moved to their own files
*/

class Game
{

};

/* Global variables 
*  TODO: to be moved to their own files
*/

//*******************************************************
// Window-related objs/funcs/vars
//*******************************************************

SDL_Window* g_window;
SDL_Surface* g_screen_surface;
constexpr int k_screen_width = 800;
constexpr int k_screen_height = 600;


/*
int main()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		
	}
	else
	{
		//Create window
		g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, k_screen_width, k_screen_height, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{

		}
		else
		{
			//Get window surface
			g_screen_surface = SDL_GetWindowSurface(g_window);

			//Fill the surface white
			SDL_FillRect(g_screen_surface, NULL, SDL_MapRGB(g_screen_surface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(g_window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(g_window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
*/