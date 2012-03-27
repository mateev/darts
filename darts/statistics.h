#ifndef STATISTICS_H
#define STATISTICS_H

#include "gameplay.h"
#include <cstdlib>					//	for rand()
#include <iostream>					//	for swap()

/*	Used for SWITCH game type */
using std::swap;

/*	The following is used to handle who goes first	*/
enum GameType
{
	JOE_FIRST = 1,
	SID_FIRST,
	SWITCH,
};

const unsigned short MAX_GAMES_COUNT = 252;
const unsigned short MIN_GAMES_COUNT = 7;

/*	Plays a set of games and returns Joe's wins as a percentage	*/
double joeGames(GameType = JOE_FIRST,long = 10000);

/*	Generates and returns frequencies of game lengths in a table */
long* frequenciesOfGameLengths(Player,long=10000);

#endif STATISTICS_H