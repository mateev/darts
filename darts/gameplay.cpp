#include "gameplay.h"

// Plays as a Player and returns how many shots it took to win
int play(Player playerSuccess, int playerScore)
{
	return focus100(playerScore,playerSuccess) + fix50(playerScore) + win(playerSuccess);
}

// This tries to lower the score to under 100; score is passed as parameter
int focus100(int& currentScore, Player successPercentage)
{
	int attemptsCount = 0;

	do
	{
		currentScore -= hitBull(successPercentage);		//	Try to hit bull and subtract the result from the current score
		attemptsCount++;								//	Increase count
	}
	while(currentScore>=100);

	return attemptsCount;								//	Return count
}

//	This function returns the attempts it took to lower the score to 50
int fix50(int &currentScore)
{
	int attemptsCount = 0;									//	This counts the attempts
	int attemptedTarget;									//	This variable will hold the current target
	int attemptResult;

	while(currentScore>50)
	{

		attemptedTarget = (currentScore-50 <= 20) ? (currentScore-50) : 20;	//	If the score can be brought down to 50 in 1 shot, will attempt to take it, otherwise will do the closest possible

		attemptsCount++;													//	Count as an attempts

		attemptResult = attemptHit(attemptedTarget);						//	Return the result of the shot

		if(currentScore-attemptResult>=50)									//	If the shot will *NOT* lower the score below 50
			currentScore-=attemptResult;										//	... counts as a valid shot and score is decreased
	}

	return attemptsCount;
}

//	This function means the player will shoot until he hits the bull
int win(Player successPercentage)
{
	int attemptsCount = 0;

	do
	{
		attemptsCount++;
	}
	while(hitBull(successPercentage)!=50);

	return attemptsCount;
}

//	This returns the points in a neighbour of a target; the paramater is the target
int returnScoreOfNeighbour(int target)
{
	if(score[1][target]==-1)						//	If player was aiming for a 20, but missed...
		return randomSign()<0 ? 1 : 5;					//	... he will get one of 1 or 5 by random

	return score[0][score[1][target]+randomSign()];	//	Otherwise return the location with an offset of one
}

//	This function attempts to hit a target and returns the result of that attempt
int attemptHit(int target)
{
	int succeededPercentage = randomPercentage();	// Get the current success calculation

	if(succeededPercentage<=80)						// If it is under 80% ...
		return target;									// ... return the target
	else											// Else ...
		return returnScoreOfNeighbour(target);			// ... return one of the target's neighbours
}

//	Player tries to hit the bull
int hitBull(Player successPercentage)
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

