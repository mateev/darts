#ifndef GAME_H
#define GAME_H

#include "dartboard.h"
#include "player.h"

enum GameType	{ JOE_PRACTICE, JOE_FIRST, SID_FIRST, SWITCH };

class Game
{
private:
	bool isOver;

	Dartboard board;

	Player playerOne;
	Player playerTwo;

	void resetPlayers();
public:
	Game();

	static const int MAX_GAMES_COUNT;

	const bool IsGameOver() const;

	void ResetGame();

	int Practice(PlayerID=JOE);
	PlayerID OneVsOne(PlayerID=JOE);
};


#endif