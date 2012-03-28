#include "game.h"

//	The maximum possible length of a game
const int Game::MAX_GAMES_COUNT = 252;		// One bull + 251 ones	

//	Tells if game is over
const bool Game::IsGameOver() const
{
	return isOver;
}

//	Provides functionality for a two-player game; returns the id of the winner
PlayerID Game::OneVsOne(PlayerID staringPlayer)
{
	if(IsGameOver())																		//	If game is over, this is a new game, so ...
		ResetGame();																			//	... reset

	Player* activePlayer = (playerOne.GetID() != staringPlayer) ? &playerOne : &playerTwo;	//	This will point to the active player during the game;
																							//	It will initialy point to the player, who will go second

	int currentTargetResult;																//	This will hold the sector at which the player is aiming at a given time
	
	do
	{
		activePlayer = (activePlayer==&playerOne) ? &playerTwo : &playerOne;								//	...the other player becomes active ...

		currentTargetResult = activePlayer->ThrowDart();													//	...and throws a dart at a sector ...

		activePlayer->ScorePoints(board.HitTarget(currentTargetResult,activePlayer->GetBullHitPercent()));	//	...and tries to collect the points of the sector, which he actualy hit

	}
	while(!activePlayer->HasWon());																			//	...until someone wins!

	isOver = true;																			// Game over!

	return activePlayer->GetID();															//	Return the id of the winner
}

int Game::Practice(PlayerID player)
{
	if(IsGameOver())																		//	If game is over, this is a new game, so ...
		ResetGame();																			//	... reset

	Player &activePlayer = (playerOne.GetID() == player) ? playerOne : playerTwo;								//	The active player will be whoever is Joe

	int currentTargetResult;																					//	This variable will hold the target result

	while(!activePlayer.HasWon())																				//	Session will continue until the player has "won"
	{
		currentTargetResult = activePlayer.ThrowDart();																//	...	record target ...
		
		activePlayer.ScorePoints(board.HitTarget(currentTargetResult,activePlayer.GetBullHitPercent()));			//	... record response from board ...
	}

	isOver = true;																			//	Game over!

	return activePlayer.GetDartsUsed();														//	Return how many darts were used
}

//	Copy constructor; the copy will be an exact copy of the original from time at which it was made
Game::Game(const Game& other)
{
	board = Dartboard();

	playerOne = other.playerOne;
	playerTwo = other.playerTwo;

	isOver = other.isOver;
}

//	Default constructor
Game::Game()
{
	board = Dartboard();
	ResetGame();
}

//	Resets players to default values
void Game::resetPlayers()
{
	playerOne = Player(JOE);
	playerTwo = Player(SID);
}

//	Resets game
void Game::ResetGame()
{
	isOver = false;
	resetPlayers();
}

