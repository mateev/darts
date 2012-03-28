#include "game.h"

const int Game::MAX_GAMES_COUNT = 252;

const bool Game::IsGameOver() const
{
	return isOver;
}

PlayerID Game::OneVsOne(PlayerID staringPlayer)
{
	if(IsGameOver())
		ResetGame();

	Player* activePlayer = (playerOne.GetID() != staringPlayer) ? &playerOne : &playerTwo;

	int currentTargetResult;
	
	do
	{
		activePlayer = (activePlayer==&playerOne) ? &playerTwo : &playerOne;

		currentTargetResult = activePlayer->ThrowDart();

		activePlayer->ScorePoints(board.HitTarget(currentTargetResult,activePlayer->GetBullHitPercent()));

	}
	while(!activePlayer->HasWon());

	isOver = true;

	return activePlayer->GetID();
}

int Game::Practice(PlayerID player)
{
	if(IsGameOver())
		ResetGame();

	Player &activePlayer = (playerOne.GetID() == player) ? playerOne : playerTwo;								//	Player will be whoever is Joe

	int currentTargetResult;																				//	This variable will hold the target result

	while(!activePlayer.HasWon())																			//	Session will continue until the player has "won"
	{
		currentTargetResult = activePlayer.ThrowDart();															//	...	record target ...
		
		activePlayer.ScorePoints(board.HitTarget(currentTargetResult,activePlayer.GetBullHitPercent()));		//	... record response from board
	}

	isOver = true;

	return activePlayer.GetDartsUsed();																		//	Return how many darts were used
}

Game::Game()
{
	board = Dartboard();
	ResetGame();
}


void Game::resetPlayers()
{
	playerOne = Player(JOE);
	playerTwo = Player(SID);
}

void Game::ResetGame()
{
	isOver = false;
	resetPlayers();
}

