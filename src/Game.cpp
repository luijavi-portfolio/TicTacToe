//******************************************************************/
// Graphics: Game.cpp
// CLASS IMPLEMENTED: Game
//******************************************************************/


#include "Game.h"
#include "Window.h"
#include <iostream>
#include <random>
#include <algorithm>


Game::Game(Window& window)
	:
	has_quit(false),
	window(window),
	gfx(window),
	board(gfx),
	mouse_pos({ 0,0 })
{
	// Assign 9 squares to vector of squares, which are mostly
	// SDL_Rect objects
	for (std::size_t i = 0; i < 9; ++i)
	{
		squares.emplace_back(Square(gfx));
	}

	// Assign values to the SDL_Rects for each of the 9 squares to place them
	// in the window
	for (int squares_down = 0; squares_down < 3; ++squares_down)
	{

		for (int squares_across = 0; squares_across < 3; ++squares_across)
		{
			std::size_t index = squares_across + squares_down * 3;
			int x = kBoardOrigin.x + squares_across * (kSquareSize + kHashTickness);
			int y = kBoardOrigin.y + squares_down * (kSquareSize + kHashTickness);
			squares.at(index).SetRect(x, y, kSquareSize, kSquareSize);
		}
	}

	InitPlayers();
}

// Main game (really, application) loop - once the user has quit 
// the application, Run() will return 0 to the main(). 
int Game::Run()
{
	SDL_Event event;

	while (!has_quit)
	{
		while (SDL_PollEvent(&event))
		{
			ProcessEvent(&event);
		}

		gfx.BeginFrame();
		UpdateLogic();
		ComposeFrame();
		gfx.EndFrame();
	}

	return 0;
}

// Processes SDL events, specifically Mouse motion and SDL_QUIT
void Game::ProcessEvent(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
		{
			SDL_PumpEvents();
			SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

		} break;
		
		case SDL_QUIT:
		{
			has_quit = true;
		} break;
	}
}

// Handles the main game logic, such as starting the game, players taking turns, and
// checking for game-ending conditions. Currently, only alternates between 2 players,
// and doesn't have any kind of AI built in. 
// TODO: I think there's an issue whereby sometimes after the game has reset, it didn't
//		 reset properly, and it maybe skips a turn. Must investigate.
void Game::UpdateLogic()
{
	if (game_started)
	{
		if (!game_over)
		{
			CurrentPlayerSelectSquare();

			// Check whether the current player has taken their turn. If so, evaluate
			// game-ending conditions
			if (players.at(current_player).TurnTaken())
			{
				if (IsThreeInARow())
				{
					// TODO: Delete all this shit
					std::cout << "Player " << (current_player + 1) << " has 3 in a row with symbol ";
					if (players.at(current_player).GetSymbol() == Square::Symbol::kO)
						std::cout << "O." << std::endl;
					else if (players.at(current_player).GetSymbol() == Square::Symbol::kX)
						std::cout << "X." << std::endl;
					else
						std::cout << "... oh shit, something went wrong..." << std::endl;

					Reset();
				}
				else if (IsDraw())
				{
					std::cout << "Is draw, yo!" << std::endl;
					Reset();
				}
				else
				{
					PassTurn();
				}
			}
		}
		else
		{
			Reset();
			std::cout << "Game over, man." << std::endl;
		}

		
	}
	else
	{
		game_started = true;
		current_player = 0;
		game_over = false;
	}
}

// Places everything to be drawn. The actual rendering happens
// in the gfx.EndFrame() function within the Run() function
void Game::ComposeFrame()
{
	// Only draws the 4 intersecting "lines" (actually rects)
	// for the hash shape. 
	board.Draw();

	// Iterates through squares vector to draw each square
	for (auto& s : squares)
	{
		// Check if the mouse cursor is over any of the rects
		if (SDL_PointInRect(&mouse_pos, s.GetRect()))
		{
			// Highlight square if it's empty
			if (s.GetSymbol() == Square::Symbol::kEmpty)
			{
				s.OnHover();
			}
		}
		s.Draw();
	}

	// TODO: Need to draw the line (rect, really) across 3-in-a-row
}

// Initializes vector of players - and gives each player a pseudo-random
// symbol (X or O)
void Game::InitPlayers()
{
	// Clears players vector, since the initialization adds a new player
	// object when the game resets.
	// TODO: This is probably hella inneficient. In fact, might only need
	//		 to create two Player objects (player_1 and player_2), and not
	//		 use a vector
	if (!players.empty())
	{
		players.clear();
	}

	// Adds 2 new Player objects to players vector, each w/ the symbol kEmpty
	for (std::size_t i = 0; i < 2; ++i)
	{
		players.emplace_back(Player());
	}

	// Initialize random device to give the first player either an X (cross) or
	// an O (circle), and give the second player the other symbol.
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 2);

	// TODO: Test that s1 is being generated as either 1 or 2 consistently
	Square::Symbol s1 = static_cast<Square::Symbol>(dist(mt));

	players.at(0).SetSymbol(s1);

	if (s1 == Square::Symbol::kO)
	{
		players.at(1).SetSymbol(Square::Symbol::kX);
	}
	else
	{
		players.at(1).SetSymbol(Square::Symbol::kO);
	}

	// TODO: Delete this iostream
	std::cout << "Current (first) player: " << current_player << std::endl;
}

// Essentially, a brute force way to check whether 3 in a row - will short circuit evaluate as
// soon as any of the 3 functions return true. 
// TODO: This is most likely very inefficient... but's it's Tic Tac Toe, so...
//		 I'll see if there's an easier way to do this.
const bool Game::IsThreeInARow() const
{
	Square::Symbol symbol_to_check = squares.at(selected_square_index).GetSymbol();

	return IsHorizontalThreeInARow(symbol_to_check)
		|| IsVerticalThreeInARow(symbol_to_check)
		|| IsDiagonalThreeInARow(symbol_to_check);
}

// Check each row for the symbol parameter being passed
const bool Game::IsHorizontalThreeInARow(const Square::Symbol& symbol) const
{
	// i increases by 3 since each row begins 3 indeces from
	// the previous row
	// TODO: This loop may be more easily readable if i was < 3, and I just
	//		 added an extra variable for the index of the squares vector to check
	for (std::size_t i = 0; i < 9; i += 3)
	{
		// As soon as a square's symbol doesn't match the symbol param,
		// the loop moves onto the next iteration, and as soon as 3 adjacent indeces
		// match the symbol param, the function returns true 
		if (squares.at(i).GetSymbol() == symbol
			&& squares.at(i + 1).GetSymbol() == symbol
			&& squares.at(i + 2).GetSymbol() == symbol)
		{
			return true;
		}
	}

	return false;
}

// Check each column for the symbol parameter being passed
const bool Game::IsVerticalThreeInARow(const Square::Symbol& symbol) const
{
	// i only increases by 1, since each column begins with the first
	// three elements of the squares vector
	for (std::size_t i = 0; i < 3; ++i)
	{
		if (squares.at(i).GetSymbol() == symbol
			&& squares.at(i + 3).GetSymbol() == symbol
			&& squares.at(i + 6).GetSymbol() == symbol)
		{
			return true;
		}
	}

	return false;
}

// First checks whether center square has the symbol being passed - returns false if not.
// Then checks the top left and short circuit evaluates to false if it doesn't have
// the symbol being passed. Continues this process for the top right, bottom left, and bottom right squares,
// depending on preceding square value results
const bool Game::IsDiagonalThreeInARow(const Square::Symbol& symbol) const
{
	static constexpr std::size_t center_square_index = 4;

	if (squares.at(center_square_index).GetSymbol() == symbol)
	{
		static constexpr std::size_t top_left_index = 0;
		static constexpr std::size_t bottom_right_index = 8;
		static constexpr std::size_t top_right_index = 2;
		static constexpr std::size_t bottom_left_index = 6;

		return (squares.at(top_left_index).GetSymbol() == symbol && squares.at(bottom_right_index).GetSymbol() == symbol)
			|| (squares.at(top_right_index).GetSymbol() == symbol && squares.at(bottom_left_index).GetSymbol() == symbol);
	}

	return false;
}

// Simply returns the number of empty squares - so it doesn't check whether it's a "true" draw,
// wherein there may be a square left to select, but it won't win anyone the game. That was
// too much thinking, and I'm about done with this game. It's tic tac toe. Come on. What do you want
// from me?!
const bool Game::IsDraw() const
{
	Square::Symbol empty = Square::Symbol::kEmpty;
	return !std::count_if(squares.cbegin(), squares.cend(), [&empty](const Square& s) {return s.GetSymbol() == empty; });
}

// sets the current_player index to either 1 or 0. 
// TODO: This may be a little dangerous? It could run the risk of the player index being negative
//		 or > than 1. May have to rethink this. 
void Game::PassTurn()
{
	players.at(current_player).ResetTurnTaken();
	current_player ? --current_player : ++current_player;

	// TODO: Delete this (or actually, have this execute only in Debug mode?)
	std::cout << "Current player: " << current_player << "\tSquare selected: " << selected_square_index << std::endl;
}

// Tracks the position of the mouse within the Window, and checks whether
// the mouse is over any of the squares with SDL_PointInRect. 
// TODO: This function will have to be changed to ignore the holding of the
//		 mouse button, since we only want to deal with individual clicks.
void Game::CurrentPlayerSelectSquare()
{
	// Mouse-related variables for the SDL Mouse events
	int x;
	int y;
	Uint32 buttons;

	SDL_PumpEvents();

	buttons = SDL_GetMouseState(&x, &y);
	SDL_Point mouse_pos = { x, y };

	int i = 0;	// Used to set the selected_square_index, which may be changed, idk.
	for (auto& s : squares)
	{
		// Check whether the mouse position is intersecting with a given square
		if (SDL_PointInRect(&mouse_pos, s.GetRect()))
		{
			// Check whether the mouse left button has been pressed (if it's down)
			if (buttons & SDL_BUTTON_LMASK)
			{
				// Confirm that the square over which the mouse button has been pressed is empty
				if (s.GetSymbol() == Square::Symbol::kEmpty)
				{
					s.SetSymbol(players.at(current_player).GetSymbol());
					players.at(current_player).SetTurnTaken(true);
					selected_square_index = i;
				}
			}
		}
		++i;
	}
}

// Resets the Game variables
void Game::Reset()
{
	game_over = true;
	game_started = false;
	for (auto& s : squares)
	{
		s.SetSymbol(Square::Symbol::kEmpty);
	}
	InitPlayers();
	
}
