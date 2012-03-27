/*
	The dartsCore module is used for general functions, 
	which arent related to the game type or game style.
*/

#ifndef DARTSCORE_H
#define DARTSCORE_H

#include <cstdlib>					// For rand()

//* The following handle score-array traversal *//
int returnScoreOfNeighbour(int);			// This returns the points of a neighbour of a target; the paramater is the target

//* The following handle points awarding when a dart hits a board *//
int hitBull(int);						// This tries to hit a bull and returns score; paramater is bull hit success percentage
int attemptHitPercentage(int,int);		// This tries to hit a number and returns the result, hit success is dependant on the success percentage
int attemptHit(int);					// This tries to hit a number and returns the result; hit success is 80%

//* The following handle random events*//
int randomSign();							// This returns -1 or 1 by random
int randomPercentage();						// This returns a random percentage
int randomScore();							// This returns an int in [1;20]

//* The following is scoreboard *//
const short score[2][21] = {{20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20},	//	This line holds the score at a given section
								{0,1,8,10,3,19,5,12,14,17,6,15,18,4,16,7,13,9,2,11,-1}};					//	This line hold at which section is the given score

#endif