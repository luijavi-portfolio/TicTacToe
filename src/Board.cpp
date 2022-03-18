//******************************************************************/
// Graphics: Board.cpp
// CLASS IMPLEMENTED: Board
//******************************************************************/

#include "Board.h"
#include <iostream>

Board::Board(Graphics& gfx_in)
	:
	gfx(gfx_in),
	hashes{}
{
	// TODO: Make hash initializing cleaner/more efficient
	// Initialize vertical lines
	// values for x and y based on allowing for some padding
	// between the window edge and the line edges
	hashes[0].x = 275;
	hashes[0].y = 45;
	hashes[0].w = kHashTickness;
	hashes[0].h = kHashLength;

	hashes[1].x = 515;
	hashes[1].y = hashes[0].y;	// 75
	hashes[1].w = kHashTickness;
	hashes[1].h = kHashLength;

	// Initialize the horizontal lines
	hashes[2].x = hashes[0].y; // 75
	hashes[2].y = hashes[0].x; // 275
	hashes[2].w = kHashLength;
	hashes[2].h = kHashTickness;

	hashes[3].x = hashes[0].y;	// 75 
	hashes[3].y = hashes[1].x;  // 515
	hashes[3].w = kHashLength;
	hashes[3].h = kHashTickness;
}

void Board::Draw()
{
	gfx.DrawRects(hashes, 4, SDL_Color{ 255, 255, 255, });
}
