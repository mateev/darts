/*
	The following is used to handle the 301 gameplay as specified by the coursework specification
*/

#ifndef GAME_H
#define GAME_H

#include "dartsCore.h"

/*	The following is used to handle who goes first	*/
enum GameType
{
	JOE_FIRST = 1,
	SID_FIRST,
	SWITCH,
};

/*	The following are used to handle player logic	*/
typedef int Player;					// Player "entity"
const Player JOE = 70;				// Joe, defined by his success rate
const Player SID = 72;				// Sid, defined by his success rate

/* The following play as different players */
int play(Player,int=301);					// Plays as a Player and returns how many shots it took to win; game can be other than 301

//*		The Following return number of shots		*//

/* Scoring phase */
int focus100(int&,Player);		// This tries to lower the score to under 100; score is passed as parameter

/* Focus phase */
int fix50(int&);				// This tries to lower the score to 50 if it is under 70; paramater is current score

/* Checkout phase */
int win(Player);						// This tries to hit the bull

#endif