#include "dartsCore.h"

const short DartsCore::score[2][21] = {{20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20},	//	This line holds the score at a given section
													{0,1,8,10,3,19,5,12,14,17,6,15,18,4,16,7,13,9,2,11,-1}};					//	This line hold at which section is the given score

//	This returns the points in a neighbour of a target; the paramater is the target
int DartsCore::returnScoreOfNeighbour(int target)
{
	if(score[1][target]==-1)						//	If player was aiming for a 20, but missed...
		return randomSign()<0 ? 1 : 5;					//	... he will get one of 1 or 5 by random

	return score[0][score[1][target]+randomSign()];	//	Otherwise return the location with an offset of one
}

// This tries to hit a number and returns the result, hit success is dependant on the success percentage
int DartsCore::attemptHit(int target,int successPercentage)
{
	int succeededPercentage = randomPercentage();	// Get the current success calculation

	if(succeededPercentage<=successPercentage)						// If it is under 80% ...
		return target;									// ... return the target
	else											// Else ...
		return returnScoreOfNeighbour(target);			// ... return one of the target's neighbours
}

/*
//	This function attempts to hit a target and returns the result of that attempt
int DartsCore::attemptHit(int target)
{
	return attemptHit(target,80);
}
*/

//	Player tries to hit the bull
int DartsCore::hitBull(int successPercentage)
{
	int succeededPercentage = randomPercentage();	// Get random number

	if(succeededPercentage <= successPercentage)	// If it is under the success percentage
		return 50;										// ... bull is hit and we return score of 50

	return randomScore();							// Player missed, so another section is hit
}

// This creates a random percentage;
int DartsCore::randomPercentage()
{
	int randomNumber;

	do
	{
		randomNumber = rand();						//	Choose a random number
	}
	while(randomNumber>=RAND_MAX-(RAND_MAX%100));	//	RAND_MAX%100 will return the last two digits of RAND_MAX, so this assures the chosen number doesn't benefit one player over the other

	return randomNumber%100;						//	Return the chosen number as a percentage
}

// Return a score between 1 and 20
int DartsCore::randomScore()
{
	int randomNumber;
	
	do
	{
		randomNumber = rand();						//	Choose a random number
	}
	while(randomNumber>=RAND_MAX-(RAND_MAX%10));	//	RAND_MAX%10 will return the last digit of RAND_MAX, so this assures the score is chosen fairly

	return 1 + (randomNumber%20);					//	return an integer in [ 1+0 ; 1+20 )
}

// This generates a random sign
int DartsCore::randomSign()
{
	int randomNumber;

	do
	{
		randomNumber = rand();
	}
	while(!(RAND_MAX & 1) && (randomNumber==RAND_MAX));	 	// If RAND_MAX is even, the odd-even ratio of all possibilities is unbalanced, since rand() returns 0 as well;

	return (randomNumber & 1) ? -1 : 1;						// If the picked number is odd return -1, otherwise 1
}
