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


int* frequenciesAndGameLengths(Player player,int attempts)
{
	// If the player is invalid:
	if(player!=JOE && player!=SID)
		return NULL;					// Return null pointer

	int* gameRatesCounter = new int[MAX_GAMES_COUNT];							// Allocate memory for the table

	for(int gamesCounter = 0; gamesCounter<MAX_GAMES_COUNT; gamesCounter++)		// Fill all members with 0
		gameRatesCounter[gamesCounter]=0;

	for(int gamesCounter = 0; gamesCounter<attempts;gamesCounter++)				// Play the game attempts-times
	{

		int currentGames = play(player);											// ... record how many throws did the current game take
		gameRatesCounter[currentGames]++;											// ... increase the counter for that ammount of throws
	}

	return gameRatesCounter;							// All went good
}

