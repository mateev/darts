#include "statistics.h"

//
Player* competitionStatistics(GameType game,int gamesCount)
{
	Player* results = new Player[gamesCount];

	switch(game)
	{
	case JOE_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = playJoeVsSid(JOE);
		}
		break;
	case SID_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = playJoeVsSid(SID);
		}
		break;
	case SWITCH_JOE_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = (gameCounter==0 ? playJoeVsSid(JOE) : (results[gameCounter-1] == JOE ? playJoeVsSid(SID) : playJoeVsSid(JOE)));
		}
		break;
	case SWITCH_SID_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = (gameCounter==0 ? playJoeVsSid(SID) : (results[gameCounter-1] == JOE ? playJoeVsSid(SID) : playJoeVsSid(JOE)));
		}
		break;
	}
	return results;
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
