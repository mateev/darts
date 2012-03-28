#ifndef GAME_H
#define GAME_H

#include "dartboard.h"
#include "player.h"

enum GameType	{ JOE_FIRST, SID_FIRST, SWITCH };

class Game
{
private:
	bool isOver;						//	Decides if game is over

	Dartboard board;					//	The board object for the game

	Player playerOne;					
	Player playerTwo;

	void resetPlayers();				//	Reset functionality for the players
public:
	Game();								//	Default constructor
	Game(const Game&);					//	Copy constructor

	const bool IsGameOver() const;		//	Tells if game is over

	void ResetGame();					//	Resets the game

	int Practice(PlayerID=JOE);			//	Provides functionality for a player to practice
	PlayerID OneVsOne(PlayerID=JOE);	//	Provides functionality for a two-player game

	static const int MAX_GAMES_COUNT;	//	The maximum possible length of a game
};


#endif