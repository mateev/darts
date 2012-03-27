#include "gameplay.h"
#include "dartsCore.h"

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
