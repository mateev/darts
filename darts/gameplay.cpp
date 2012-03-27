#include "gameplay.h"

// This plays a Joe vs Sid game
Player playJoeVsSid(Player firstPlayer)
{
	Player secondPlayer = firstPlayer == JOE ? SID : JOE;			// If the first player is Joe, the second will be Sid and vice versa

	int firstPlayerGame = play(firstPlayer);						// First player plays by himself
	int secondPlayerGame = play(secondPlayer);						// Second player plays by himself

	if(firstPlayerGame > secondPlayerGame)						// If first player's attempts count is bigger than the second player's
	{
		return secondPlayer;										// ... first player looses
	}
	else 
	{
		return firstPlayer;											// ... second player looses
	}
}

// plays as joe
int playJoe()
{
	return play(JOE);
}

// plays as sid
int playSid()
{
	return play(SID);
}



// Returns attempts until win
int play(Player bullSuccessRate)
{
	int attempts = 0;	// This variable counts the attempts it took
	int score = 301;	// This variable holds the score

	GameState currentState = scoring;	// A game begins with a scoring phase

	while(currentState!=win)		// game loop
	{
		//	states decision
		if(score<100)
		{
			if(score>70)
				currentState = focus70;
			else if(score<=70 && score>50)
				currentState = focus50;
			else if(score==50)
				currentState = checkout;
			else
				currentState = win;
		}
	
		switch(currentState)
		{
		case scoring:
			attempts += tryToLowerToBelow100(score,bullSuccessRate);// try to lower below 100 and record how long it took
			break;
		case focus70:
			attempts +=	tryToLowerTo70Below100(score);	// try to lower to 70 and record how long it took
			break;
		case focus50:
			attempts+=tryToLowerBelow70To50(score);		// try to lower to 50
			score = 50;									// score has been lowered to 50, so the variable score:=50
			break;
		case checkout:
			attempts+=tryToWin(bullSuccessRate);		// try to win
			currentState = win;							// won
			break;
		}
	}

	return attempts;
}

// This tries to lower the score to under 100; score is passed as parameter
int tryToLowerToBelow100(int& currentScore, Player successPercentage)
{
	int attemptsCount = 0;

	int score = currentScore;

	while(score>=100)
	{
		score -= throwBull(successPercentage);
		attemptsCount++;
	}

	currentScore = score;
	return attemptsCount;
}

// This tries to hit the bull
int tryToWin(Player successPercentage)
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

//	This function returns the attempts it took to lower the score to 50
int tryToLowerBelow70To50(int currentScore)
{
	int attemptsCount = 1;													// This varible counts the attempts it took

	int hitAttemptScoreValue = hitAttemptScore(currentScore-50);			// This variable holds the result of the attempt
																			//	to hit (currentScore-50)

	if(hitAttemptScoreValue!=currentScore-50)								// If the hit was not successfull...
	{
		if(currentScore-hitAttemptScoreValue<50)								// ... and (score-(what we've hit))<50
			attemptsCount += tryToLowerBelow70To50(currentScore);					// ... try to hit (20-score) again ...
		else if(currentScore-hitAttemptScoreValue>50)							// ... and (score-(what we've hit))>50 ...
			attemptsCount += tryToLowerBelow70To50(currentScore-hitAttemptScoreValue);// ... try to hit (score-what we've hit) again ...
	}

	return attemptsCount;													// Return attempts count :-]
}

//	This function tries to lower the score to less than 70
int tryToLowerTo70Below100(int& currentScore)
{
	int attemptsCount = 0;													// Counts the attempts it took

	while(currentScore>70)															// While score>70 ...
		currentScore -= hitAttemptScore(20);											// ... throw at 20

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

	// Generate a number from 0-21 to pick a random section of the board, *other* than the bull
	successCalculator = rand() % 21;

	// ... return the points that this section awards
	return score[successCalculator];
}

int justifiedRandom()
{
	// Generate a number from 0-100 to figure out if bull hit was a success
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
	return rand()%2 == 0 ? -1 : 1;
}