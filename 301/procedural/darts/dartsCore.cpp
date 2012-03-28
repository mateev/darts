#include "dartsCore.h"

//	This returns the points in a neighbour of a target; the paramater is the target
int returnScoreOfNeighbour(int target)
{
	if(score[1][target]==-1)						//	If player was aiming for a 20, but missed...
		return randomSign()<0 ? 1 : 5;					//	... he will get one of 1 or 5 by random

	return score[0][score[1][target]+randomSign()];	//	Otherwise return the location with an offset of one
}

// This tries to hit a number and returns the result, hit success is dependant on the success percentage
int attemptHit(int target,int successPercentage)
{
	int succeededPercentage = randomPercentage();	// Get the current success calculation

	if(succeededPercentage<=successPercentage)						// If it is under 80% ...
		return target;									// ... return the target
	else											// Else ...
		return returnScoreOfNeighbour(target);			// ... return one of the target's neighbours
}


//	Player tries to hit the bull
int hitBull(int successPercentage)
{
	int succeededPercentage = randomPercentage();	// Get random number

	if(succeededPercentage <= successPercentage)	// If it is under the success percentage
		return 50;										// ... bull is hit and we return score of 50

	return randomScore();							// Player missed, so another section is hit
}

// This creates a random percentage;
int randomPercentage()
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
int randomScore()
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
int randomSign()
{
	int randomNumber;

	do
	{
		randomNumber = rand();
	}
	while(!(RAND_MAX & 1) && (randomNumber==RAND_MAX));	 	// If RAND_MAX is even, the odd-even ratio of all possibilities is unbalanced, since rand() returns 0 as well;

	return (randomNumber & 1) ? -1 : 1;						// If the picked number is odd return -1, otherwise 1
}
