#ifndef STATISTICS_H
#define STATISTICS_H

#include "gameplay.h"
#include <cstdlib>					// For rand()

const unsigned short MAX_GAMES_COUNT = 301 - 50;
const unsigned short MIN_GAMES_COUNT = 7;

/*	The following is used to handle who goes first	*/
enum GameType
{
	JOE_FIRST = 0,
	SID_FIRST,
	SWITCH_JOE_FIRST,
	SWITCH_SID_FIRST
};

Player* competitionStatistics(GameType,int=10000);
int* frequenciesAndGameLengths(Player,int=10000);	// Prints out number of throws, games count and percentage in a table; return the table itself

#endif STATISTICS_H