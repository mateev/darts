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
typedef unsigned short Player;		// Player "entity"
const Player JOE = 70;				// Joe, defined by his success rate
const Player SID = 72;				// Sid, defined by his success rate

/* The following play as different players */
int play(Player);					// returns attempts until win
int playJoe();						// plays as joe
int playSid();						// plays as sid
Player playTwoPlayers(Player,Player);	// This plays a Joe vs Sid game, asuming Joe plays first


//* The Following return the number of attempts *//

/* Scoring phase */
int focus100(int&,Player);		// This tries to lower the score to under 100; score is passed as parameter

/* Focus phase */
int focus70(int&);			// This tries to lower the score to 50; paramater is current score
int fix50(int&);				// This tries to lower the score to 50 if it is under 70; paramater is current score

/* Checkout phase */
int win(Player);						// This tries to hit the bull

//* The following handle score-array traversal *//
int returnScoreOfNeighbour(int);			// This returns the points of a neighbour of a target; the paramater is the target

//* The following handle points awarding when a dart hits a board *//
int throwBull(Player);						// This tries to hit a bull and returns score; paramater is bull hit success percentage
int hitAttemptScore(int);					// This tries to hit a number and returns the result

//* The following are "system functions"*//
int randomSign();							// This returns -1 or 1 by random
int justifiedRandom();						// Returns a fixed random

const unsigned score[21] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20};

#endif