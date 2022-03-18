//******************************************************************/
// FILE: Window.h
// CLASS PROVIDED: Include file for Window class, which is a wrapper 
// for the SDL_Window class
//******************************************************************/

#pragma once

#include "Graphics.h"
#include <string>

class Window
{
	friend Graphics::Graphics(Window&);
public:
	Window(std::string title, int width, int height);
	Window(const Window&) = delete;
	~Window();
	Window& operator=(const Window&) = delete;
private:
	SDL_Window* window;
};