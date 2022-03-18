//******************************************************************/
// FILE: Graphics.h
// CLASS PROVIDED: Graphics - a wrapper class for the SDL_Renderer
//******************************************************************/

#pragma once

#include <SDL.h>
#include <array>

class Graphics
{
public:
	Graphics(class Window& window);
	Graphics(const Graphics&) = delete;
	~Graphics();
	Graphics& operator=(const Graphics&) = delete;
	void BeginFrame();
	void EndFrame();
	void PutPixel(int x, int y, SDL_Color c);
	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color c);
	void DrawRect(const SDL_Rect* rect, SDL_Color c);
	void DrawRects(const SDL_Rect* rects, int num_rects, SDL_Color c);

private:
	static constexpr int kScreenWidth = 800;
	static constexpr int kScreenHeight = 800;
	SDL_Renderer* renderer;
};