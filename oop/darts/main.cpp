#include <iostream>
#include <ctime>
#include "dartboard.h"
#include "player.h"

using namespace std;

enum GameType	{ JOE_FIRST, SID_FIRS, SWITCH };

class Game
{
private:
	GameType type;

	bool isOver;

	Dartboard board;

	Player playerOne;
	Player playerTwo;

	void resetPlayers();

public:
	Game(GameType = JOE_FIRST);

	const bool IsGameOver() const { return isOver; }
	void ResetGame(GameType);
};

Game::Game(GameType inputType)
{
	board = Dartboard();

	ResetGame(inputType);
}

void Game::resetPlayers()
{
	PlayerID firstPlayer;

	if(type==SWITCH)
		firstPlayer = DartsCore::randomSign() < 0 ? JOE : SID;
	else
		firstPlayer = (type==JOE_FIRST) ? JOE : SID;

	playerOne = Player(firstPlayer);
	playerTwo = Player(firstPlayer==JOE ? SID : JOE);
}

void Game::ResetGame(GameType inputType)
{
	type = inputType;
	resetPlayers();
}


int main()
{
	srand(time(0));
	Dartboard board;

	Player first(PlayerID::JOE);
	Player second(PlayerID::SID);

	cout << first.GetName() << endl << second.GetName() << endl;

	swap(first,second);

	cout << first.GetName() << endl << second.GetName() << endl;


	return 0;
}

