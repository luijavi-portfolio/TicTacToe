//******************************************************************/
// FILE: Square.cpp
// CLASS IMPLEMENTED: Square
//******************************************************************/

#include "Square.h"

void Square::OnHover()
{
	gfx.DrawRect(&rect, SDL_Color{ 0,255,0,0 });
}

void Square::Draw()
{
	switch (symbol)
	{
		case Square::Symbol::kEmpty:
		{

		} break;
		case Square::Symbol::kX:
		{
			DrawX();
		} break;
		case Square::Symbol::kO:
		{
			DrawO();
		} break;
	}
}

void Square::DrawX()
{
	constexpr int padding = 20;		// Padding between edge of cross and hash on the board
	constexpr int kNumLines = 40;	// Number of lines for thickness


	for (int x_offset = padding; x_offset < kNumLines; ++x_offset)
	{
		int x1 = rect.x + x_offset;
		int y1 = rect.y + padding;
		int x2 = (rect.x + rect.w - padding * 3) + x_offset; // Get the x coordinate of the right edge and subtract 3 x padding
		int y2 = rect.y + rect.h - padding;

		gfx.DrawLine(x1, y1, x2, y2, SDL_Color{ 255,255,255,0 });
		gfx.DrawLine(x2, y1, x1, y2, SDL_Color{ 255,255,255,0 });
	}

}

void Square::DrawO()
{
	SDL_Color c1 = { 255, 255, 255, 0 };
	SDL_Color c2 = { 0, 0, 0, 0};
	int radius = (rect.w - 30) / 2;

	int x = (rect.x + rect.w / 2);
	int y = (rect.y + rect.h / 2);

	// Outer circle
	for (int w = 0; w < radius * 2; ++w)
	{
		for (int h = 0; h < radius * 2; ++h)
		{
			int dx = radius - w;	// horizontal offset
			int dy = radius - h;	// vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				gfx.PutPixel(x + dx, y + dy, c1);
			}
		}
	}

	// Inner circle
	radius -= 30;	
	for (int w = 0; w < radius * 2; ++w)
	{
		for (int h = 0; h < radius * 2; ++h)
		{
			int dx = radius - w;	// horizontal offset
			int dy = radius - h;	// vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				gfx.PutPixel(x + dx, y + dy, c2);
			}
		}
	}
}