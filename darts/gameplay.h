#ifndef GAME_H
#define GAME_H

#include <cstdlib>					// For rand()

/*	The following are used to handle player logic	*/
typedef unsigned short Player;		// Player "entity"
const Player JOE = 70;				// Joe, defined by his success rate
const Player SID = 72;				// Sid, defined by his success rate

/* The following play as different players */
int play(Player);					//returns attempts until win
int playJoe();						// plays as joe
int playSid();						// plays as sid
Player playJoeVsSid(Player=JOE);	// This plays a Joe vs Sid game, asuming Joe plays first


//* The Following return the number of attempts *//

/* Scoring phase */
int tryToLowerToBelow100(int&,Player);		// This tries to lower the score to under 100; score is passed as parameter

/* Focus phase */
int tryToLowerTo70Below100(int&);			// This tries to lower the score to 50; paramater is current score
int tryToLowerBelow70To50(int);				// This tries to lower the score to 50 if it is under 70; paramater is current score

/* Checkout phase */
int tryToWin(int);							// This tries to hit the bull

//* The following handle score-array traversal *//
int returnScoreOfNeighbour(int);			// This returns the points of a neighbour of a target; the paramater is the target
int randomSign();							// This returns -1 or 1 by random

//* The following handle points awarding when a dart hits a board *//
int throwBull(Player);						// This tries to hit a bull and returns score; paramater is bull hit success percentage
int hitAttemptScore(int);					// This tries to hit a number and returns the result

const unsigned score[21] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20};

#endif