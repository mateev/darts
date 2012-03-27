#ifndef STATISTICS_H
#define STATISTICS_H

#include "gameplay.h"
#include <cstdlib>					// For rand()

const unsigned short MAX_GAMES_COUNT = 252;
const unsigned short MIN_GAMES_COUNT = 7;

/*	The following is used to handle who goes first	*/
enum GameType
{
	JOE_FIRST = 0,
	SID_FIRST,
	SWITCH,
};

Player* competitionStatistics(GameType,int=10000);
long* frequenciesOfGameLengths(Player,long=10000);	//	Generates and returns frequencies of game lengths statistics table

#endif STATISTICS_H