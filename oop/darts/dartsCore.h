/*
	The dartsCore module is used for general functions, 
	which arent related to the game type or game style.
*/

#ifndef DARTSCORE_H
#define DARTSCORE_H

#include <cstdlib>					// For rand()

class DartsCore
{
public:
	static const int BullValue = 50;

	//* The following handle score-array traversal *//
	static int returnScoreOfNeighbour(int);			// This returns the points of a neighbour of a target; the paramater is the target

	//* The following handle points awarding when a dart hits a board *//
	static int hitBull(int);						// This tries to hit a bull and returns score; paramater is bull hit success percentage
	static int attemptHit(int,int=80);					// This tries to hit a number and returns the result, hit success is dependant on the success percentage
//	static int attemptHit(int);						// This tries to hit a number and returns the result; hit success is 80%

	//* The following handle random events*//
	static int randomSign();							// This returns -1 or 1 by random
	static int randomPercentage();						// This returns a random percentage
	static int randomScore();							// This returns an int in [1;20]

	//* The following is scoreboard *//
	static const short score[2][21];
};


#endif