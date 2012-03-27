#include "statistics.h"

double joeGames(GameType type,long gamesCount)
{
	Player firstPlayer;
	Player secondPlayer;

	int firstWinsCounter = 0;
	int secondWinsCounter = 0;

	if(type!=SWITCH)									//	If it's not a switch game
		firstPlayer = (type==JOE_FIRST ? JOE : SID);		//	... first player is chosen, depending on the game type
	else
		firstPlayer = randomSign() < 0 ? JOE : SID;		//	Otherwise the first player is chosen via a coin toss
	
	secondPlayer = (firstPlayer==JOE ? SID : JOE);		//	Second player is chosen, based on the first player choice

	for(long tr = 0;tr<gamesCount;tr++)						//	Going over the games
	{
		int firstPlay  = play(firstPlayer);						//	First player plays by himself
		int secondPlay = play(secondPlayer);					//	Second player plays by himself

		if(firstPlay<=secondPlay)								//	If the first player won faster than the second player ...
		{
			firstWinsCounter++;											// ... increase wins count

			if(type==SWITCH)									//	If it's a switch game
			{
				swap(firstPlayer,secondPlayer);						//	Players swap
				swap(firstWinsCounter,secondWinsCounter);							//	and keep their wins counts
			}

		}
		else
		{
			secondWinsCounter++;										//	Otherwise second player wins
		}

	}

	if(firstPlayer==JOE)										//	Return Joe's statistics
		return (double)firstWinsCounter*100/(gamesCount);
	else
		return (double)secondWinsCounter*100/(gamesCount);
}

//	Generates and returns frequencies of game lengths statistics table
long* frequenciesOfGameLengths(Player player,long attempts)
{
	if(player!=JOE && player!=SID)	// If the player is invalid ...
		return NULL;					// ... return null pointer

	long* records = new long[MAX_GAMES_COUNT];	// This array will hold the statistic records

	for(int i = 0;i<MAX_GAMES_COUNT;i++)		// Initialize each element
	{
		records[i] = 0;
	}

	for(long attempt = 0; attempt<attempts; attempt++)	//	Attempt to win, until desired count is reached
	{
		records[play(player)-1]++;							// Record how long it took to play a game
	}

	return records;				// Return the records
}
