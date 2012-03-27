#ifndef GAME_H
#define GAME_H

#include <cstdlib>					// For rand()

/*	The following is used for the game fsm */
enum GameState
{
	scoring = 0,
	fixing50,
	checkout,
	won
};

/*	The following are used to handle player logic	*/
typedef int Player;					// Player "entity"
const Player JOE = 70;				// Joe, defined by his success rate
const Player SID = 72;				// Sid, defined by his success rate

/* The following play as different players */
int play(Player);					// Plays as a Player and returns how many shots it took to win

//* The Following return the number of attempts *//

/* Scoring phase */
int focus100(int&,Player);		// This tries to lower the score to under 100; score is passed as parameter

/* Focus phase */
int fix50(int&);				// This tries to lower the score to 50 if it is under 70; paramater is current score

/* Checkout phase */
int win(Player);						// This tries to hit the bull

//* The following handle score-array traversal *//
int returnScoreOfNeighbour(int);			// This returns the points of a neighbour of a target; the paramater is the target

//* The following handle points awarding when a dart hits a board *//
int hitBull(Player);						// This tries to hit a bull and returns score; paramater is bull hit success percentage
int attemptHit(int);					// This tries to hit a number and returns the result

//* The following are "system functions"*//
int randomSign();							// This returns -1 or 1 by random
int randomPercentage();						// This returns a random percentage
int randomScore();

const short score[2][21] = {{20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20},
								{0,1,8,10,3,19,5,12,14,17,6,15,18,4,16,7,13,9,2,11,-1}};

#endif