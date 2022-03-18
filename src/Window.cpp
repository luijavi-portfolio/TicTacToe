//******************************************************************/
// FILE: Window.cpp
// CLASS IMPLEMENTED: Window wrapper class
//******************************************************************/

#include "Window.h"
#include <iostream>

Window::Window(std::string title, int width, int height)
	:
	window(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL. SDL Error: " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "Failed to create window! SDL Error: " << SDL_GetError() << std::endl;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}
