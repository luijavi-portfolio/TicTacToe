//******************************************************************/
// FILE: Board.h
// CLASS PROVIDED: Board - essentially only used to draw the hashes
//	for the game
// TODO: Consider simplifying this? Or is this okay? IDK.
//******************************************************************/

#pragma once

#include "Graphics.h"
#include <vector>
#include <array>

class Board
{
public:
	Board(Graphics& gfx);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	void Draw();
private:
	static constexpr int kNumHashes = 4;
	static constexpr int kHashLength = 710;
	static constexpr int kHashTickness = 10;
	Graphics& gfx;
	SDL_Rect hashes[kNumHashes];
};