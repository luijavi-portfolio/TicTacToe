//******************************************************************/
// FILE: Game.h
// CLASS PROVIDED: Game - holds main logic for Game, as well as
//	SDL_Event processing
//******************************************************************/

#pragma once

#include "Graphics.h"
#include "Board.h"
#include "Square.h"
#include "Player.h"
#include <vector>

class Game
{
public:
	Game(class Window& window);
	int Run();
private:
	void ProcessEvent(SDL_Event* event);
	void UpdateLogic();
	void ComposeFrame();
	void InitPlayers();
	void PassTurn();
	void CurrentPlayerSelectSquare();
	void Reset();
	const bool IsThreeInARow() const;
	const bool IsHorizontalThreeInARow(const Square::Symbol& symbol) const;
	const bool IsVerticalThreeInARow(const Square::Symbol& symbol) const;
	const bool IsDiagonalThreeInARow(const Square::Symbol& symbol) const;
	const bool IsDraw() const;
private:
	bool has_quit;
	bool game_started = false;
	bool game_over = false;
	int current_player = 0;
	int selected_square_index = -1;			// TODO: Game::selected_square_index might be a stale member var
	static constexpr int kNumSquares = 9;
	static constexpr int kSquareSize = 230;
	static constexpr int kHashTickness = 10;
	static constexpr int kNumHashes = 4;
	static constexpr int kHashLength = 710;
	static constexpr SDL_Point kBoardOrigin{ 45, 45 };
	std::vector<Square> squares;
	std::vector<Player> players;
	Window& window;
	Graphics gfx;
	Board board;
	SDL_Point mouse_pos;
};