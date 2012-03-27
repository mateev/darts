#include "gameplay.h"

Player playTwoPlayers(Player firstPlayer,Player secondPlayer)
{
	int firstPlayerResult = play(firstPlayer);
	int secondPlayerResult = play(secondPlayer);

	return (firstPlayerResult>=secondPlayerResult) ? firstPlayer : secondPlayer;
}

// Returns attempts until win
int play(Player bullSuccessRate)
{
	int attempts = 0;	// This variable counts the attempts it took
	int score = 301;	// This variable holds the score

	GameState currentState = scoring;	// A game begins with a scoring phase

	while(currentState!=won)		// game loop
	{
		switch(currentState)
		{
		case scoring:
			attempts += focus100(score,bullSuccessRate);// try to lower below 100 and record how long it took
			break;
		case fixing50:
			attempts += fix50(score);		// try to lower to 50
			score = 50;									// score has been lowered to 50, so the variable score:=50
			break;
		case checkout:
			attempts += win(bullSuccessRate);		// try to win
			score = 0;
			break;
		}

		//	states decision
		if(score<100)
		{
			if(score==50)
				currentState = checkout;
			else if(score>50)
				currentState = fixing50;
			else
				currentState = won;
		}
	}

	return attempts;
}

// This tries to lower the score to under 100; score is passed as parameter
int focus100(int& currentScore, Player successPercentage)
{
	int attemptsCount = 0;

	while(currentScore>=100)
	{
		currentScore -= throwBull(successPercentage);
		attemptsCount++;
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
	while(throwBull(successPercentage)!=50);

	return attemptsCount;
}

//	This returns the points of a neighbour of a target; the paramater is the target
int returnScoreOfNeighbour(int target)
{
	int selectedIndex = -1;

	for(int i =0;i<21;i++)
	{
		if(score[i]==target)
		{
			selectedIndex = i;
			break;
		}
	}

	if(selectedIndex==0 || selectedIndex==20)
		return randomSign()<0 ? 1 : 5;

	return score[selectedIndex+randomSign()];



	/*
	if(target==20)							// If target is 20 ...
	{
		return randomSign()<0 ? 1 : 5;		// ... choose one of the 20s at random
	}
	else									// Or else ...
	{
		for(int i = 0;i<21;i++)					// ... find the target in the array, add +/- 1 to the index and return the value
			if(score[i]==target)
				return score[i+randomSign()];
	}

	return -1;	// Error somewhere
	*/
}

//	This function attempts to hit a target and returns if it has hit or not
int hitAttemptScore(int target)
{
	int successCalculation = justifiedRandom();		// Get the current success calculation

	successCalculation %= 100;

	if(successCalculation<80)						// If it is under 80% ...
		return target;									// ... return the target
	else											// Else ...
		return returnScoreOfNeighbour(target);			// ... return one of the target's neighbours

}

#include <iostream>

//	This function returns the attempts it took to lower the score to 50
int fix50(int &currentScore)
{
	int attemptsCount = 0;
	int attemptedTarget = 0;

	while(currentScore>=70)
	{
		currentScore -= hitAttemptScore(20);
		attemptsCount++;
	}

	do
	{
		attemptedTarget = currentScore-50;
		attemptsCount++;

		if(hitAttemptScore(attemptedTarget)==attemptedTarget)
		{
			currentScore -= attemptedTarget;
		}
	}
	while(currentScore!=50);

	return attemptsCount;
}

//	This function tries to lower the score to less than 70
int focus70(int& currentScore)
{
	int attemptsCount = 0;													// Counts the attempts it took

	do
	{
		currentScore -= hitAttemptScore(20);											// ... throw at 20
		attemptsCount++;																// ... indicate a throw
	}
	while(currentScore>=70);															// While score>70 ...

	return attemptsCount;													// Return the attempts it took
}

//	This function tries to throw the bull
int throwBull(Player successPercentage)
{
	// Get random number
	int successCalculator = justifiedRandom();

	// Get success percentage
	successCalculator %= 100;

	if(successCalculator < successPercentage)		// If it is under the success percentage
		return 50;										// ... bull is hit and we return score of 50

	// Generate a number from [0;21) to pick a random section of the board, *other* than the bull
	successCalculator = rand() % 21;

	// ... return the points that this section awards
	return score[successCalculator];
}

int justifiedRandom()
{
	int randomNumber;

	do
	{
		randomNumber = rand();
	}
	while(randomNumber>32700);

	return randomNumber;
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