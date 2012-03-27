#include "gameplay.h"


int play(Player currentPlayer)
{
	int playerScore = 301;
	return focus100(playerScore,currentPlayer) + fix50(playerScore) + win(currentPlayer);
}

// This tries to lower the score to under 100; score is passed as parameter
int focus100(int& currentScore, Player successPercentage)
{
	int attemptsCount = 0;

	do
	{
		currentScore -= hitBull(successPercentage);
		attemptsCount++;
	}
	while(currentScore>=100);

	return attemptsCount;
}

//	This function returns the attempts it took to lower the score to 50
int fix50(int &currentScore)
{
	int attemptsCount = 0;									//	This counts the attempts
	int attemptedTarget;								//	This variable will hold the current target
	int attemptResult;

	while(currentScore>50)
	{

		attemptedTarget = (currentScore-50 <= 20) ? (currentScore-50) : 20;
		attemptsCount++;

		attemptResult = attemptHit(attemptedTarget);

		if(currentScore-attemptResult>=50)
			currentScore-=attemptResult;
	}

	return attemptsCount;
}

// This tries to hit the bull
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

//	This returns the points of a neighbour of a target; the paramater is the target
int returnScoreOfNeighbour(int target)
{
	if(score[1][target]==-1)
		return randomSign()<0 ? 1 : 5;

	return score[0][score[1][target]+randomSign()];
}

//	This function attempts to hit a target and returns if it has hit or not
int attemptHit(int target)
{
	int succeededPercentage = randomPercentage();		// Get the current success calculation

	if(succeededPercentage<80)						// If it is under 80% ...
		return target;									// ... return the target
	else											// Else ...
		return returnScoreOfNeighbour(target);			// ... return one of the target's neighbours

}

//	This function tries to throw the bull
int hitBull(Player successPercentage)
{
	int succeededPercentage = randomPercentage();	// Get random number

	if(succeededPercentage < successPercentage)		// If it is under the success percentage
		return 50;										// ... bull is hit and we return score of 50

	return randomScore();					
}

// This creates a random percentage
int randomPercentage()
{
	int randomNumber;

	do
	{
		randomNumber = rand();
	}
	while(randomNumber>RAND_MAX-(RAND_MAX/10));

	return randomNumber%100;
}

// Return a score between 1 and 20
int randomScore()
{
	int randomNumber = rand();
	
	do
	{
		randomNumber = rand();
	}
	while(randomNumber>RAND_MAX-(RAND_MAX%10));

	return 1 + (randomNumber%20);
}

// This generates a random sign
int randomSign()
{
	int randomNumber = rand();
	
	// If RAND_MAX is even, the odd-even ratio is unbalanced, since rand() returns 0 as well;
	while(!(RAND_MAX & 1) && (randomNumber==RAND_MAX))	 // If RAND_MAX is even and that number is selected
	{
		randomNumber = rand();								// ... select another
	}

	return (randomNumber & 1) ? -1 : 1;
}

