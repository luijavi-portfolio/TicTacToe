//******************************************************************/
// Graphics: Graphics.cpp
// CLASS IMPLEMENTED: Graphics
//******************************************************************/

#include "Window.h"
#include "Graphics.h"
#include <iostream>


Graphics::Graphics(Window& window)
	:
	renderer(nullptr)
{
	renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		std::cout << "Failed to create renderer. SDL Error: " << SDL_GetError() << std::endl;
	}
}

// Calls SDL_DestroyRenderer and sets renderer to nullptr
Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}

// Clears the frame
void Graphics::BeginFrame()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
}

// Calls SDL_RenderPresent
void Graphics::EndFrame()
{
	SDL_RenderPresent(renderer);
}

// Calls SDL_RenderDrawPoint w/ given x and y coordinate and SDL_Color
void Graphics::PutPixel(int x, int y, SDL_Color c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(renderer, x, y);
}

// Calls SDL_RenderDrawLine with given x1, x2, y1, and y2 coordinates, and SDL_Color
void Graphics::DrawLine(int x1, int y1, int x2, int y2, SDL_Color c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// Calls SDL_RenderFillRect w/ SDL_Rect* and SDL_Color
void Graphics::DrawRect(const SDL_Rect* rect, SDL_Color c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer, rect);
}

// Calls SDL_RenderFillRects w/ SDL_Rect*, number of rects and SDL_Color
void Graphics::DrawRects(const SDL_Rect* rects, int num_rects, SDL_Color c)
{
	SDL_SetRenderDrawColor(renderer,c.r, c.g, c.b, c.a);
	SDL_RenderFillRects(renderer, rects, num_rects);
}