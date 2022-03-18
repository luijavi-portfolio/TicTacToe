//******************************************************************/
// FILE: Square.h
// CLASS PROVIDED: Square - a class for managing the state and 
//	rendering of the squares on the board.
// ENUM CLASS PROVIDED: Symbol - used for the state of the square;
//	either it's empty (kEmpty), is occupied by a cross/X (kX), or
//	a circle/doughnut/O (kO)
//******************************************************************/

#pragma once
#include "Graphics.h"

class Square
{
public:
	enum class Symbol { kEmpty, kX, kO };
public:
	Square(Graphics& gfx)
		:
		gfx(gfx),
		rect{},
		symbol{ Symbol::kEmpty }
	{ }
	/*Square(const Square&) = delete;*/
	/*Square& operator=(const Square&) = delete;*/
	void SetRect(int x, int y, int w, int h)
	{
		rect = { x, y, w, h };
	}
	void SetSymbol(Symbol symbol_in) { symbol = symbol_in; }
	const Symbol GetSymbol() const { return symbol; }
	SDL_Rect* GetRect() { return &rect; }
	const SDL_Rect* GetRect() const { return &rect; }
	void OnHover();
	void Draw();
private:
	void DrawX();
	void DrawO();
private:
	Graphics& gfx;
	SDL_Rect rect;
	Symbol symbol;
};