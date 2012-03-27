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

struct GameStatistics
{
	unsigned short attempts;
	unsigned short count;
};

Player* competitionStatistics(GameType,int=10000);
GameStatistics* frequenciesOfGameLengths(Player,int&,int=10000);	//	Generates and returns frequencies of game lengths statistics table
void addNewStatisticsRecord(GameStatistics* &,int&,int);			//	Adds a new record to the statistics table


#endif STATISTICS_H