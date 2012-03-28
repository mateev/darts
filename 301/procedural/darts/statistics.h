/*
	The statistics module is used for generating statistics, based on the 301 coursework
*/

#ifndef STATISTICS_H
#define STATISTICS_H

#include "gameplay.h"
#include <cstdlib>					//	for rand()
#include <iostream>					//	for swap()

/*	Used for SWITCH game type */
using std::swap;

/*	This variable holds the maximum throws count that a game can take - 251 ones and one bull	*/
const unsigned short MAX_GAMES_COUNT = 252;

/*	Plays a set of games and returns Joe's wins as a percentage	*/
double joeGames(GameType = JOE_FIRST,long = 10000);

/*	Generates and returns frequencies of game lengths in a table */
long* frequenciesOfGameLengths(Player,long=10000);

#endif STATISTICS_H