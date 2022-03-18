//******************************************************************/
// FILE: Player.h
// CLASS PROVIDED: Player - used to track which symbol each player 
//	has, and whether they've taken their turn.
//******************************************************************/

#pragma once

#include "Square.h"
#include <vector>

class Player
{
public:
	Player()
		:
		symbol(Square::Symbol::kEmpty)
	{};
	Player(const Player&) = default;
	Player& operator=(Player&& p) noexcept { return *this; }
	/*void SelectSquare(std::vector<Square>& squares);*/
	Square::Symbol GetSymbol() const { return symbol; }
	const bool TurnTaken() const { return turn_taken; }
	void SetSymbol(Square::Symbol symbol_in) { symbol = symbol_in; }
	void SetTurnTaken(bool has_taken_turn) { turn_taken = has_taken_turn; }
	void ResetTurnTaken() { turn_taken = false; }
private:
	bool turn_taken = false;
	Square::Symbol symbol;
};